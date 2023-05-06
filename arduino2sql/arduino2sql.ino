#include <SoftwareSerial.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Set up the GSM shield SIM900
SoftwareSerial sim900(7, 8); // RX, TX
String apn = "Orange";
String user = "Orange";
String password = "Orange";

// Set up the MySQL database connection
IPAddress server_ip(127, 0, 0, 1); // Replace with your server IP address
char user = "root";
char password = "";
char database = "arduino2sql";
MySQL_Connection conn((Client *)&sim900);
MySQL_Cursor cur(&conn);

void setup() {
  // Start the serial communication with the SIM900
  sim900.begin(19200);
  
  // Set up the GSM connection
  delay(5000);
  sim900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"APN\",\"" + apn + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"USER\",\"" + user + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"PWD\",\"" + password + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=1,1");
  delay(5000);
  
  // Set up the MySQL connection
  conn.connect(server_ip, 3306, user, password);
}

void loop() {
  // Prepare the data to be sent to the MySQL database
  String data1 = 80;
  String data2 = 17;
  
  // Execute an INSERT statement to insert the data into the table
  cur.execute("INSERT INTO arduinotable (humidity, temperature) VALUES (" + data1 + ", " + data2 + ")");
  delay(1000);
}
