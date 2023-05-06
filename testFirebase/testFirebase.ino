#include <FBJS_Config.h>
#include <FirebaseJson.h>
#include <MB_List.h>
#include <MB_String.h>

#include <Config.h>
#include <Firebase_Arduino_WiFi101.h>
#include <Firebase_TCP_Client.h>
#include <WCS.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial gsmSerial(9, 10); // RX, TX

// const char * FIREBASE_HOST = "mitio-miaad69.firebaseapp.com";
// const char * FIREBASE_AUTH = "WxmA8HXOb2jNGtUW7oZNar5e8BJ78LN4AuHUNjWa";

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  
  Firebase.begin("mitio-miaad69.firebaseapp.com", "WxmA8HXOb2jNGtUW7oZNar5e8BJ78LN4AuHUNjWa", &gsmSerial);
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