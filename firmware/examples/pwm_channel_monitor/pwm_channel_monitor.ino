// SAD receiver CH1 PWM monitor — reconstructed example, NOT original tested sketch.
// Use for receiver-only USB-powered test. Keep servo LiPo disconnected.
const byte rxPin = A0;
void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(115200);
}
void loop() {
  unsigned long pwmUs = pulseIn(rxPin, HIGH, 30000UL);
  if (pwmUs >= 900 && pwmUs <= 2100) {
    Serial.print(F("CH1 pulse (us): "));
    Serial.println(pwmUs);
  } else {
    Serial.println(F("No valid CH1 signal"));
  }
  delay(100);
}
