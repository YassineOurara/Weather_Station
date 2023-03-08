#include "DHT.h"
#define DHTPIN 12
  
// Definit le type de capteur utilise
#define DHTTYPE DHT11
  
// Declare un objet de type DHT
// Il faut passer en parametre du constructeur 
// de l'objet la broche et le type de capteur
DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  Serial.begin(9600);
    
  // Initialise la capteur DHT11
  dht.begin();
}
  
void loop() {
  // Recupere la temperature et l'humidite du capteur et l'affiche
  // sur le moniteur serie
  Serial.println("Temperature = " + String(dht.readTemperature())+" °C");
  Serial.println("Humidité = " + String(dht.readHumidity())+" %");
  
  // Attend 10 secondes avant de reboucler
  delay(10000);
}