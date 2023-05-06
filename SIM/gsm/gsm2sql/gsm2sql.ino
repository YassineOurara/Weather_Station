#include <GSM.h>

// Set up the GSM shield SIM900
GSM gsmAccess;
const char* GPRS_APN = "your_apn";
const char* GPRS_LOGIN = "your_username";
const char* GPRS_PASSWORD = "your_password";

// Set up the internet connection
GPRS gprs;
GPRSClient client;

void setup() {
  // Start the serial communication with the GSM shield SIM900
  Serial.begin(9600);
  
  // Initialize the GSM shield SIM900
  while (gsmAccess.begin() != GSM_READY) {
    delay(1000);
  }
  
  // Set the APN, username, and password of your mobile network operator
  gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD);
}

void loop() {
  // Check if the GPRS connection is established
  if (gsmAccess.isAccessAlive()) {
    // Connect to the internet and send HTTP requests
    if (client.connect("www.example.com", 80)) {
      client.println("GET / HTTP/1.1");
      client.println("Host: www.example.com");
      client.println("Connection: close");
      client.println();
      delay(1000);
      
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
      }
      
      client.stop();
    }
  }
  
  delay(10000);
}
