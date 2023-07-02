#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
//  #define moisturePin 36 //A0
// const int moisturePin = 33; //A5
// const int moisturePin = A0; //A0
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const int moisturePin = A0;
int pourcentage = 0;
const char* ssid = "TP-LINK_5A3FD6";
const char* password = "43642670";
const char* serverURL = "http://192.168.1.105/lms/htsendesp32.php";

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();
  int temValue =  sensors.getTempCByIndex(0);

  int moistureValue = analogRead(moisturePin);

  // Serial.println(moistureValue);
  int moisturePercentage = map(moistureValue, 1023, 0, 0, 100);
  // int moisturePercentage = ( 100 - ( (moistureValue/4095.00) * 100 ) );
  sendMoistureData(moisturePercentage);
  sendtempData(temValue);
  // sendMoistureData(moistureValue);

  // pourcentage = Conversion(moistureValue);
  // sendMoistureData(pourcentage);
  delay(1000);
}
// int Conversion(int value) {
//   int ValeurPorcentage = 0;
//   ValeurPorcentage = map(value, 1023, 0, 0, 100);
//   return ValeurPorcentage;
// }
void sendMoistureData(int moisture) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String postData = "moisture=" + String(moisture);
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
    Serial.println(postData);
    Serial.print("HTTP code: ");
    Serial.println(httpCode);
  }
}


void sendtempData(int temp) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String postData = "temperature=" + String(temp);
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
