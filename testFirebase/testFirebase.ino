#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial gsmSerial(9, 10); // RX, TX

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, &gsmSerial);
}

void loop() {
  // Create a JSON document
  DynamicJsonDocument doc(200);
  doc["sensor"] = "temperature";
  doc["value"] = 25.5;
  
  // Serialize the JSON document to a string
  String json;
  serializeJson(doc, json);
  
  // Push the JSON string to Firebase
  Firebase.pushString("/data", json);
  
  // Print the JSON string to Serial Monitor
  Serial.println(json);
  
  delay(1000);
}