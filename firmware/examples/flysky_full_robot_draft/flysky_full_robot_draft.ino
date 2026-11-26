#include <Servo.h>

// SAD FlySky control: Uno + FS-iA10B in PPM mode, six channels
// CH1/CH2: right joystick. CH5: SWC (SAFE/ARM/DRIVE).
// CH6: SWD (Servo 1-2 / Servo 3-4).
// This is a cautious bench draft, not a certified radio failsafe.

const byte PPM_PIN = 2;
const byte SERVO_PINS[4] = {8, 9, 10, 11};
const byte ENA = 5, IN1 = 12, IN2 = 3;
const byte ENB = 6, IN3 = 4, IN4 = 7;

const int SERVO_MIN = 60;
const int SERVO_MAX = 120;
const int STICK_CENTER = 1500;
const int DEADZONE = 75;
const byte MAX_MOTOR_PWM = 160;
const byte MIN_MOTOR_PWM = 120;
const int MOTOR_DEADZONE = 110;
const unsigned long SIGNAL_TIMEOUT_US = 150000UL;

// A complete six-channel PPM frame is copied at the next sync gap.
// Unlike some PPMReader versions, this decoder can detect missing frames.
volatile uint16_t ppmChannels[6] = {0, 0, 0, 0, 0, 0};
volatile uint16_t pendingChannels[6];
volatile byte ppmCount = 0;
volatile bool ppmBadFrame = false;
volatile unsigned long lastEdgeUs = 0;
volatile unsigned long lastGoodFrameUs = 0;

void ppmEdge() {
  unsigned long now = micros();
  unsigned long delta = now - lastEdgeUs;
  lastEdgeUs = now;

  if (delta > 2500UL) {
    if (ppmCount >= 6 && !ppmBadFrame) {
      for (byte i = 0; i < 6; i++) ppmChannels[i] = pendingChannels[i];
      lastGoodFrameUs = now;
    }
    ppmCount = 0;
    ppmBadFrame = false;
  } else {
    if (ppmCount < 6) {
      if (delta >= 900 && delta <= 2100) {
        pendingChannels[ppmCount] = (uint16_t)delta;
      } else {
        ppmBadFrame = true;
      }
    }
    if (ppmCount < 20) ppmCount++;
  }
}

Servo joints[4];
int jointAngle[4] = {90, 90, 90, 90};
unsigned long jointStepMs[4] = {0, 0, 0, 0};
int motorDirection[2] = {0, 0};
unsigned long motorPauseUntil[2] = {0, 0};

enum Mode { SAFE, ARM, DRIVE };
int previousMode = SAFE;
bool visitedSafe = false;
bool driveReady = false;
bool armReady = false;
int previousPair = -1;
unsigned long lastReportMs = 0;

bool sticksCentered(uint16_t ch1, uint16_t ch2) {
  return abs((int)ch1 - STICK_CENTER) <= DEADZONE &&
         abs((int)ch2 - STICK_CENTER) <= DEADZONE;
}

int stickAxis(uint16_t v) {
  int offset = constrain((int)v - STICK_CENTER, -500, 500);
  return abs(offset) <= DEADZONE ? 0 : offset;
}

int decodeMode(uint16_t ch5) {
  if (ch5 <= 1250) return SAFE;
  if (ch5 >= 1750) return DRIVE;
  if (ch5 >= 1350 && ch5 <= 1650) return ARM;
  return SAFE;
}

void stopMotor(byte index) {
  if (index == 0) {
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void stopAllMotors() {
  stopMotor(0);
  stopMotor(1);
  motorDirection[0] = motorDirection[1] = 0;
  motorPauseUntil[0] = motorPauseUntil[1] = 0;
}

void setMotor(byte index, int command) {
  int desired = command > 0 ? 1 : (command < 0 ? -1 : 0);
  if (desired == 0 || abs(command) < MOTOR_DEADZONE) {
    stopMotor(index);
    motorDirection[index] = 0;
    return;
  }

  if (motorDirection[index] != 0 && desired != motorDirection[index]) {
    stopMotor(index);
    motorDirection[index] = 0;
    motorPauseUntil[index] = millis() + 120;
    return;
  }
  if ((long)(millis() - motorPauseUntil[index]) < 0) {
    stopMotor(index);
    return;
  }

  byte pwm = map(constrain(abs(command), MOTOR_DEADZONE, 500),
                 MOTOR_DEADZONE, 500, MIN_MOTOR_PWM, MAX_MOTOR_PWM);
  if (index == 0) {
    digitalWrite(IN1, desired > 0 ? HIGH : LOW);
    digitalWrite(IN2, desired > 0 ? LOW : HIGH);
    analogWrite(ENA, pwm);
  } else {
    digitalWrite(IN3, desired > 0 ? HIGH : LOW);
    digitalWrite(IN4, desired > 0 ? LOW : HIGH);
    analogWrite(ENB, pwm);
  }
  motorDirection[index] = desired;
}

void updateJoint(byte index, uint16_t input) {
  int offset = stickAxis(input);
  if (offset == 0) return;

  unsigned long interval = map(constrain(abs(offset), DEADZONE, 500),
                               DEADZONE, 500, 60, 15);
  unsigned long now = millis();
  if (now - jointStepMs[index] < interval) return;
  jointStepMs[index] = now;

  jointAngle[index] = constrain(jointAngle[index] + (offset > 0 ? 1 : -1),
                                SERVO_MIN, SERVO_MAX);
  joints[index].write(jointAngle[index]);
}

void setup() {
  Serial.begin(115200);
  const byte motorPins[] = {ENA, IN1, IN2, IN3, IN4, ENB};
  for (byte i = 0; i < 6; i++) pinMode(motorPins[i], OUTPUT);
  stopAllMotors();

  for (byte i = 0; i < 4; i++) {
    joints[i].attach(SERVO_PINS[i]);
    joints[i].write(jointAngle[i]);
  }

  pinMode(PPM_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PPM_PIN), ppmEdge, RISING);
  Serial.println("SAD FlySky: CH5 SWC SAFE/ARM/DRIVE, CH6 SWD servo pair");
  Serial.println("Start in SAFE, sticks centered. Keep wheels raised.");
}

void loop() {
  uint16_t ch[6];
  unsigned long goodAt;
  noInterrupts();
  for (byte i = 0; i < 6; i++) ch[i] = ppmChannels[i];
  goodAt = lastGoodFrameUs;
  interrupts();

  bool signalOK = goodAt != 0 && (micros() - goodAt < SIGNAL_TIMEOUT_US);
  for (byte i = 0; i < 6; i++) {
    if (ch[i] < 900 || ch[i] > 2100) signalOK = false;
  }

  if (!signalOK) {
    stopAllMotors();
    visitedSafe = false;
    armReady = driveReady = false;
    previousPair = -1;
  } else {
    int mode = decodeMode(ch[4]);
    if (mode != previousMode) {
      stopAllMotors();
      armReady = driveReady = false;
      previousPair = -1;
      previousMode = mode;
    }

    bool centered = sticksCentered(ch[0], ch[1]);
    if (mode == SAFE) {
      stopAllMotors();
      visitedSafe = true;
    } else if (!visitedSafe) {
      stopAllMotors();
    } else if (mode == ARM) {
      stopAllMotors();
      int pair = ch[5] < 1300 ? 0 : (ch[5] > 1700 ? 1 : -1);
      if (pair != previousPair) {
        armReady = false;
        previousPair = pair;
      }
      if (pair != -1) {
        if (centered) armReady = true;
        if (armReady) {
          updateJoint(pair * 2, ch[0]);
          updateJoint(pair * 2 + 1, ch[1]);
        }
      }
    } else {
      if (!driveReady && centered) driveReady = true;
      if (!driveReady) {
        stopAllMotors();
      } else {
        int throttle = stickAxis(ch[1]);
        int steering = stickAxis(ch[0]);
        setMotor(0, constrain(throttle + steering, -500, 500));
        setMotor(1, constrain(throttle - steering, -500, 500));
      }
    }
  }

  if (millis() - lastReportMs >= 400) {
    lastReportMs = millis();
    Serial.print(signalOK ? "PPM OK " : "PPM LOST ");
    Serial.print("CH1="); Serial.print(ch[0]);
    Serial.print(" CH2="); Serial.print(ch[1]);
    Serial.print(" CH5="); Serial.print(ch[4]);
    Serial.print(" CH6="); Serial.print(ch[5]);
    Serial.print(" | Servos=");
    for (byte i = 0; i < 4; i++) {
      Serial.print(jointAngle[i]);
      if (i < 3) Serial.print(',');
    }
    Serial.println();
  }
}