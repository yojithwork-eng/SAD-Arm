// Bench test only. PPM on D2, servo signals on D8/D9.
// This PPMReader version can keep old values after signal loss.
#include <PPMReader.h>
#include <Servo.h>

PPMReader ppm(2, 6);
Servo servo1, servo2;

const int minAngle = 60;
const int maxAngle = 120;
const int centerUs = 1500;
const int deadzoneUs = 65;

int angle1 = 90;
int angle2 = 90;
unsigned long lastMove1 = 0;
unsigned long lastMove2 = 0;
unsigned long lastPrint = 0;

void moveJoint(Servo &servo, int &angle, unsigned long &lastMove, unsigned long pulse) {
  if (pulse < 900 || pulse > 2100) return;

  int offset = constrain((int)pulse - centerUs, -500, 500);
  if (abs(offset) <= deadzoneUs) return;

  unsigned long interval = map(abs(offset), deadzoneUs, 500, 120, 30);
  unsigned long now = millis();
  if (now - lastMove < interval) return;

  lastMove = now;
  angle = constrain(angle + (offset > 0 ? 1 : -1), minAngle, maxAngle);
  servo.write(angle);
}

void setup() {
  Serial.begin(115200);
  servo1.attach(8);
  servo2.attach(9);
  servo1.write(angle1);
  servo2.write(angle2);
}

void loop() {
  unsigned long ch1 = ppm.latestValidChannelValue(1, 0);
  unsigned long ch2 = ppm.latestValidChannelValue(2, 0);

  moveJoint(servo1, angle1, lastMove1, ch1);
  moveJoint(servo2, angle2, lastMove2, ch2);

  if (millis() - lastPrint >= 250) {
    lastPrint = millis();
    Serial.print("CH1: ");
    Serial.print(ch1);
    Serial.print(" | Servo 1: ");
    Serial.print(angle1);
    Serial.print("   CH2: ");
    Serial.print(ch2);
    Serial.print(" | Servo 2: ");
    Serial.println(angle2);
  }
}
