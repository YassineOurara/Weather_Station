#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <String.h>
#include <ESPmDNS.h>

#define RXD2 16
#define TXD2 17
String moist = "";
String temp = "";

int pourcentage = 0;
// const char* ssid = "TP-LINK_5A3FD6";
// const char* password = "43642670";
// const char* serverURL = "http://192.168.1.105/lms/htsendesp32.php";
// const char* ssid = "LINGUA CAFE II";
// const char* password = "ABCD2022";
// const char* serverURL = "http://192.168.1.119/lms/htsendesp32.php";
const char* ssid = "Yassine";
const char* password = "AaBbCc@#@#@#2022";
const char* serverURL = "http://192.168.1.19/lms/htsendesp32.php";




void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  connectWiFi();
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    
    // Split the received data using the delimiter
    int delimiterIndex = data.indexOf(',');
    if (delimiterIndex != -1) {
      String value1String = data.substring(0, delimiterIndex);
      String value2String = data.substring(delimiterIndex + 1);

      int value1 = value1String.toInt();
      int value2 = value2String.toInt();

      // Process the received values
      // ...
      
      // Print the received values
      Serial.print("Hum: ");
      Serial.println(value1);
      Serial.print("Temp: ");
      Serial.println(value2);

      sendData(value1, value2);
    }
  }
  // String moist = Serial2.readString();
  // // String temp = Serial2.readString();

  // int moistureValue = moist.toInt();
  // int temValue = temp.toInt();
  // Serial.println(moistureValue);

  // sendMoistureData(moistureValue);
  // sendtempData(0);
  delay(1000);

  // Serial.println(moisturePercentage);
  // int moisturePercentage = ( 100 - ( (moistureValue/4095.00) * 100 ) ); 
  // Serial.println(moist);
  // int moistureValue = analogRead(moisturePin);
  // Serial.println(moistureValue);
  // sendMoistureData(moistureValue);
  // pourcentage = Conversion(moistureValue);
  // sendMoistureData(pourcentage);

}
void sendData(int moisture, int temperature) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String postData = "moisture=" + String(moisture) + "&temperature=" + String(temperature);
    http.begin(client, serverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(postData);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String response = http.getString();
        Serial.println(response);
      } else {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    Serial.print("Moisture Data: ");
    Serial.println(moisture);
    Serial.print("Temperature Data: ");
    Serial.println(temperature);
    Serial.print("HTTP code: ");
    Serial.println(httpCode);
  }
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
