#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

int PIN = 13; //pin2 = GPIO13 (D7)
IPAddress server_addr(127,0,0,1);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "root";        // MySQL user login password

// Sample query
char INSERT_SQL[] = "SELECT * FROM primerparcial.temperatura";

// WiFi card example
char ssid[] = "RODRIGUEZ";         // your SSID
char pass[] = "{IZZI:m5s2n9bz}";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.());

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{
  if (conn.connected())
    cursor->execute(INSERT_SQL);

  delay(5000);
}
