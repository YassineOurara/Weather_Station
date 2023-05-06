#include <SoftwareSerial.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Set up the GSM shield SIM900
SoftwareSerial sim900(7, 8); // RX, TX
String apn = "internet.orange.ma";
String gsm_user = "MEDINET";
String gsm_password = "MEDINET";

// Set up the MySQL database connection
IPAddress server_ip(127, 0, 0, 1); // Replace with your server IP address
char db_user[] = "root@localhost";
char db_password[] = "";
char db_name[] = "arduino2sql";
MySQL_Connection conn((Client *)&sim900);
MySQL_Cursor cur(&conn);

void setup() {
  // Start the serial communication with the SIM900
  sim900.begin(19200);
  
  // Set up the GPRS connection
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"APN\",\"" + apn + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"USER\",\"" + gsm_user + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=3,1,\"PWD\",\"" + gsm_password + "\"");
  delay(1000);
  sim900.println("AT+SAPBR=1,1");
  delay(10000);
  sim900.println("AT+HTTPINIT");
  delay(1000);
  
  // Set up the MySQL connection
  conn.connect(server_ip, 3306, db_user, db_password, db_name);
}

void loop() {
  // Prepare the data to be sent to the MySQL database
  int data1 = 80;
  int data2 = 17;
  
  // Execute an INSERT statement to insert the data into the table
  char sql_insert_query[100];
  sprintf(sql_insert_query, "INSERT INTO arduinotable (humidity, temperature) VALUES (%d, %d)", data1, data2);
  cur.execute(sql_insert_query);
  delay(1000);
  
  // Send an HTTP POST request to a PHP script on the server to update the database
  sim900.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);
  // sim900.println("AT+HTTPPARA=\"URL\",\"http://localhost/lms/gsm2sql.php?humidity=" + data1 + "&temperature=" + data2 + "\"");

  char url[100];
  sprintf(url, "http://localhost/lms/gsm2sql.php?humidity=%d&temperature=%d", data1, data2);
  sim900.println("AT+HTTPPARA=\"URL\",\"" + String(url) + "\"");


  delay(1000);
  sim900.println("AT+HTTPACTION=0");
  delay(10000);
}
