// SAD Option B incremental servo control — DRAFT, NOT PHYSICALLY TESTED.
// Unloaded bench test ONLY; missing complete robot safety failsafe.
// FlySky receiver CH1 PWM signal -> Uno A0.
// MG996R orange -> Uno D8. Servo power from separate buck ~5.0V.
// CRITICAL buck OUT- -> Uno GND. Do not send servo current through Uno.
#include <Servo.h>
const byte rxPin = A0, servoPin = 8;
const int minDeg = 60, maxDeg = 120, centerUs = 1500, deadzoneUs = 65;
Servo servo1;
int angleDeg = 90;
unsigned long lastStepMs = 0;

void setup() {
  Serial.begin(115200);
  pinMode(rxPin, INPUT);
  servo1.attach(servoPin);
  servo1.write(angleDeg);
}

void loop() {
  unsigned long widthUs = pulseIn(rxPin, HIGH, 30000UL);
  // Missing/invalid signal: retain current target; NOT a full failsafe.
  if (widthUs < 900 || widthUs > 2100) return;
  int offset = constrain((int)widthUs - centerUs, -500, 500);
  if (abs(offset) <= deadzoneUs) return;
  unsigned long stepMs = map(abs(offset), deadzoneUs, 500, 125, 30);
  unsigned long now = millis();
  if (now - lastStepMs >= stepMs) {
    lastStepMs = now;
    angleDeg = constrain(angleDeg + (offset > 0 ? 1 : -1),
                         minDeg, maxDeg);
    servo1.write(angleDeg);
  }
}
