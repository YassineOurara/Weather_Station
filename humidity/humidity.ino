#include <Wire.h>
#define PinAnalogiqueHumidite 0
int pourcentage = 0;
int hsol;
void setup() {
  Serial.begin(9600);
  pinMode(PinAnalogiqueHumidite, INPUT);

}

void loop() {
 hsol = analogRead(PinAnalogiqueHumidite);
 pourcentage = Conversion(hsol);

    Serial.println(pourcentage);
    delay(20);

  }
 int Conversion(int value){
 int ValeurPorcentage = 0;
 ValeurPorcentage = map(value, 1023, 0, 0, 100);
 Serial.println(ValeurPorcentage);
 return ValeurPorcentage;
  }