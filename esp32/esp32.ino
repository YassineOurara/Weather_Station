void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("ESP32 Test");
}

void loop() {
  Serial.println("Hello, world!");
  delay(1000);
}
