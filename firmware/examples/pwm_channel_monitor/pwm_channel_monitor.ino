// Recreated CH1 reader, not the exact sketch from our first test.
// Receiver-only test: A0 from FlySky CH1 signal, Uno powered by USB.
const byte rxPin = A0;

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long pwmUs = pulseIn(rxPin, HIGH, 30000UL);
  if (pwmUs >= 900 && pwmUs <= 2100) {
    Serial.print(F("CH1 (us): "));
    Serial.println(pwmUs);
  } else {
    Serial.println(F("No valid CH1 signal"));
  }
  delay(100);
}
