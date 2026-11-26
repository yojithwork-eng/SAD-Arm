// SAD - four-servo and two-motor bench test
// Commands in Serial Monitor: 1, 2, 3, 4, a, b, p, x
// This is a wiring/actuator test, NOT radio failsafe code.

#include <Servo.h>
#include <PPMReader.h>

PPMReader ppm(2, 6);            // FlySky PPM signal on D2
Servo servos[4];
const byte servoPins[4] = {8, 9, 10, 11};

const byte ENA = 5;
const byte IN1 = 12;             // D2 is already used for PPM
const byte IN2 = 3;
const byte IN3 = 4;
const byte IN4 = 7;
const byte ENB = 6;

const byte testPWM = 160;        // 0-255; short motor test only

enum TestMode { IDLE, SERVO_TEST, MOTOR_TEST };
TestMode mode = IDLE;
byte selected = 0;
byte phase = 0;
unsigned long phaseStarted = 0;

void stopMotor(byte motor) {
  if (motor == 0) {
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void stopMotors() {
  stopMotor(0);
  stopMotor(1);
}

void runMotor(byte motor, bool forward) {
  stopMotor(motor);
  if (motor == 0) {
    digitalWrite(IN1, forward ? HIGH : LOW);
    digitalWrite(IN2, forward ? LOW : HIGH);
    analogWrite(ENA, testPWM);
  } else {
    digitalWrite(IN3, forward ? HIGH : LOW);
    digitalWrite(IN4, forward ? LOW : HIGH);
    analogWrite(ENB, testPWM);
  }
}

void printMenu() {
  Serial.println();
  Serial.println("SAD BENCH TEST");
  Serial.println("1-4: test that servo (75 -> 105 -> 90 degrees)");
  Serial.println("a: test Motor A (forward -> stop -> reverse -> stop)");
  Serial.println("b: test Motor B (forward -> stop -> reverse -> stop)");
  Serial.println("p: print FlySky PPM channels 1-4");
  Serial.println("x: stop motors / cancel current sequence");
}

void startServoTest(byte index) {
  selected = index;
  mode = SERVO_TEST;
  phase = 0;
  phaseStarted = millis();
  servos[selected].write(75);
  Serial.print("Testing Servo ");
  Serial.println(selected + 1);
}

void startMotorTest(byte index) {
  selected = index;
  mode = MOTOR_TEST;
  phase = 0;
  phaseStarted = millis();
  Serial.print("Testing Motor ");
  Serial.println(index == 0 ? 'A' : 'B');
  runMotor(index, true);
}

void updateTest() {
  if (mode == IDLE) return;
  unsigned long elapsed = millis() - phaseStarted;

  if (mode == SERVO_TEST && elapsed >= 700) {
    if (phase == 0) {
      servos[selected].write(105);
      phase = 1;
    } else {
      servos[selected].write(90);
      mode = IDLE;
      Serial.println("Servo sequence finished. Check movement visually.");
    }
    phaseStarted = millis();
  }

  if (mode == MOTOR_TEST) {
    if (phase == 0 && elapsed >= 600) {
      stopMotor(selected);
      phase = 1;
      phaseStarted = millis();
    } else if (phase == 1 && elapsed >= 300) {
      runMotor(selected, false);
      phase = 2;
      phaseStarted = millis();
    } else if (phase == 2 && elapsed >= 600) {
      stopMotor(selected);
      mode = IDLE;
      Serial.println("Motor sequence finished. Check movement visually.");
    }
  }
}

void setup() {
  Serial.begin(115200);

  const byte motorPins[] = {ENA, IN1, IN2, IN3, IN4, ENB};
  for (byte i = 0; i < 6; i++) pinMode(motorPins[i], OUTPUT);
  stopMotors();

  for (byte i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90);
  }

  printMenu();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'x' || command == 'X') {
      stopMotors();
      mode = IDLE;
      Serial.println("Stopped/cancelled.");
    } else if (command == '\n' || command == '\r') {
      // Ignore line endings sent by Serial Monitor.
    } else if (mode != IDLE) {
      Serial.println("Test is running. Send x to cancel.");
    } else if (command >= '1' && command <= '4') {
      startServoTest(command - '1');
    } else if (command == 'a' || command == 'A') {
      startMotorTest(0);
    } else if (command == 'b' || command == 'B') {
      startMotorTest(1);
    } else if (command == 'p' || command == 'P') {
      for (byte ch = 1; ch <= 4; ch++) {
        Serial.print("CH");
        Serial.print(ch);
        Serial.print(": ");
        Serial.print(ppm.latestValidChannelValue(ch, 0));
        Serial.print(ch == 4 ? '\n' : ' ');
      }
    } else if (command == 'h' || command == 'H') {
      printMenu();
    } else {
      Serial.println("Unknown command. Send h for help.");
    }
  }
  updateTest();
}
