// Libraries to use io platform
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Library to work with Wi-Fi
#include <WiFi.h>

// Wi-Fi data to connecto to the network
#define WIFI_SSID "RODRIGUEZ"
#define WIFI_PASS "{IZZI:m5s2n9bz}"

// Data to connect to the adafruit io platform
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "rafaelroguz"
#define MQTT_PASS "1cee6e836738402582666a4a98ed154c"

// Object to manage Wi-Fi connection
WiFiClient client;
// Creates a new mqtt object with the previous data
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
// Will publish updates to the feed "AlarmON"
Adafruit_MQTT_Publish alarmFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/alarm");

// The pin where the pir sensor will be connected
int pinPir = 34;

// Sensor value
int sensor = 0;

// The pin where the LED indicator will be connected
//const int pinLed = 5;

// State of the alarm
bool alarmOn = false;

void connectToWiFi() {
  Serial.print("\n\nConnecting to Wifi...");
  
  // Try connection with Wi-Fi network
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Keep trying connection...
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConected to Wi-Fi!");
}

void setup() {
  Serial.begin(9600)  ;

  connectToWiFi();
  
  pinMode(pinPir, INPUT);
  //pinMode(pinLed, OUTPUT);
}

void loop() {
  //Connects/Reconnects to MQTT
  //MQTT_connect();
  
  sensor = digitalRead(pinPir);
  Serial.println(sensor);
  
  if(sensor) {
    //digitalWrite(pinLed, HIGH);
  } else {
    //digitalWrite(pinLed, LOW);
  }
}

// Connects to the MQTT server on the adafruit platform
void MQTT_connect() {
  // If there's already a connection, exit the function
  if (mqtt.connected() && mqtt.ping()) {
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  Serial.print("Connecting to MQTT...");
  uint8_t retries = 3;

  // Tries to connecte to the MQTT server. If it fails 3 times, resets the board
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    
    if (retries == 0) {
      ESP.restart();
    }
  }
  
  Serial.println("MQTT Connected!");
}
