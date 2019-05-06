// Libraries to use io platform
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Library to work with Wi-Fi
#include "WiFi.h"

// Library to use the temperatureFeed sensor DHT11
#include <DHT.h>

// Wi-Fi data to connecto to the network
//#define WIFI_SSID "Roguz"
//#define WIFI_PASS "WIFIh4anw8"
#define WIFI_SSID "RODRIGUEZ"
#define WIFI_PASS "{IZZI:m5s2n9bz}"

// Data to connect to the adafruit io platform
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "rafaelroguz"
#define MQTT_PASS "1cee6e836738402582666a4a98ed154c"

// The pin where the temperatureFeed sensor will be connected
#define DHTPIN 14
// Declares the use of the DHT11
#define DHTTYPE DHT11

// Initialices the use of the DHT11
DHT dht(DHTPIN, DHTTYPE);

// The pin where the lights will be connected
int pinLights = 13;
// The pin where the buzzer will be connected
int pinBuzzer = 16;
// The pin where the Pir Movement sensor will be connected
int pinPir = 32;

WiFiClient client;

// Creates a new mqtt object with the previous data
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

// Subscribe to the updates on the feed "Request"
Adafruit_MQTT_Subscribe requestFeed = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/request");

// Will publish updates to the feed "Temperature"
Adafruit_MQTT_Publish temperatureFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/temperature");

// Will publish updates to the feed "AlarmON"
Adafruit_MQTT_Publish alarmFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/alarmon");


void setup() {
  
  Serial.begin(9600);
  Serial.print("\n\nConnecting to Wifi...");
  
  // Try connection with Wi-Fi network
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Keep trying connection...
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConected to Wi-Fi!");

  // Subscribe to the updates on the "request" feed
  mqtt.subscribe(&requestFeed);

  // Declare the lights pin as an output
  pinMode(pinLights, OUTPUT);
  // Make sure the lights are OFF at begining
  digitalWrite(pinLights, LOW);

  // Declare the buzzer pin as an output
  pinMode(pinBuzzer, OUTPUT);

  // Make sure the buzzer is OFF at begining
  digitalWrite(pinBuzzer, LOW);

  // Declare the Pir pir as input
  pinMode(pinPir, INPUT);

  // Beging execution of the DHT11
  dht.begin();
  
}

void loop() {
  
  // Connect/Reconnect to MQTT
  MQTT_connect();
    
  // Check the state of the alarm
  bool isAlarmOn = checkAlarm();

  if (isAlarmOn) {
    toggleAlarm(isAlarmOn);
    alarmFeed.publish("ON");
  } else {
    toggleAlarm(isAlarmOn);
    alarmFeed.publish("OFF");
    
    // Reads the temperature from the sensor
    float temp = getTemperature();
  
    // Read from our subscription queue until we run out, or
    // wait up to 5 seconds for subscription to update
    Adafruit_MQTT_Subscribe * subscription;
  
    // While there are any request on the subscription queue...
    while ((subscription = mqtt.readSubscription(5000))) {
      //If we're in here, a subscription updated...
      if (subscription == &requestFeed) {
        //Print the new value to the serial monitor
        Serial.print("Got new request: ");
        Serial.println((char*) requestFeed.lastread);
        Serial.println("");
  
        // Process the request...
        if (!strcmp((char*) requestFeed.lastread, "LIGHTS_ON")) {
          // Turn on the lights
          digitalWrite(pinLights, HIGH);
        } else if (!strcmp((char*) requestFeed.lastread, "LIGHTS_OFF")) {
          // Turn off the lights
          digitalWrite(pinLights, LOW);
        } else if (!strcmp((char*) requestFeed.lastread, "TEMPERATURE")) {
          // Publish the temperature value to the "temperature" feed
          temperatureFeed.publish(temp);
        }
      }
    }
  }
    
}

// Checks the Pir sensor for movement
bool checkAlarm() {
  int value = digitalRead(pinPir);

  if (value == HIGH) 
    return true;
  else 
    return false;
}

// Toggles the alarm ON/OFF
void toggleAlarm(bool state) {
  if (state) {
    digitalWrite(pinLights, HIGH);
    digitalWrite(pinBuzzer, HIGH);
    delay(500);
    digitalWrite(pinLights, LOW);
    digitalWrite(pinBuzzer, LOW);
  } else {
    digitalWrite(pinLights, LOW);
    digitalWrite(pinBuzzer, LOW);
  }
}

// Gets the temperature from the DHT11 temperature sensor
float getTemperature() {
  
  // Humidity level
  float h = dht.readHumidity();
  // Temperature
  float t = dht.readTemperature();

 // If there's an errore obtaining the values from the sensor, returns cero
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return 0.0;
  }

  // Heat index
  float hic = dht.computeHeatIndex(t, h, false);

  // Prints the obtained values on the serial monitor
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");

  return t;
  
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
