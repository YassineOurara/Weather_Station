#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
#include <Wire.h>
#define PinAnalogiqueHumidite A0
int pourcentage = 0;
int hsol;
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 10
int i = 0;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  pinMode(PinAnalogiqueHumidite, INPUT);
    
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 


  StaticJsonDocument<200> doc;
  hsol = analogRead(PinAnalogiqueHumidite);
  pourcentage = Conversion(hsol);

  doc["id"] = i;
  doc["Humidity"] = pourcentage;
  doc["Temperature"] = sensors.getTempCByIndex(0);
  i++;
  char jsonBuffer[256];
      serializeJson(doc, jsonBuffer);

  if (i == 1) {
    Serial.print("[");
  } else {
    Serial.print(",");
  }
  Serial.print(jsonBuffer);
  if (i == 500) {
    Serial.println("]");
    i = 0;
  }
  delay(500); 
}

int Conversion(int value){
  int ValeurPorcentage = 0;
  ValeurPorcentage = map(value, 1023, 0, 0, 100);
  return ValeurPorcentage;
}