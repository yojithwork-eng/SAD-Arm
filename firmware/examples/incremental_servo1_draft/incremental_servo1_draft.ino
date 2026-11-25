// Draft only. Not tested yet; no complete radio-loss failsafe.
// Receiver CH1 -> A0, servo signal -> D8. Servo needs its own 5V buck,
// and the buck's OUT- needs to connect to Arduino GND.
#include <Servo.h>

const byte rxPin = A0;
const byte servoPin = 8;
const int minDeg = 60, maxDeg = 120;
const int centerUs = 1500, deadzoneUs = 65;

Servo servo1;
int angleDeg = 90;
unsigned long lastStepMs = 0;

void setup() {
  pinMode(rxPin, INPUT);
  servo1.attach(servoPin);
  servo1.write(angleDeg);
}

void loop() {
  unsigned long widthUs = pulseIn(rxPin, HIGH, 30000UL);

  // Hold the last angle if the signal is missing. Not a safety failsafe.
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
