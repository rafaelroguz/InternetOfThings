// Libraries to use io platform
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Library to work with Wi-Fi
#include <WiFi.h>

// Library to use the temperatureFeed sensor DHT11
#include <DHT.h>

// Wi-Fi data to connecto to the network
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
int pinLights = 23;
// The pin where the Pir Movement sensor will be connected
int pinPir = 18;
// The pin where the LED indicator will be connected
int pinLed = 13;
// The pin where the buzzer will be connected
int pinBuzzer = 26;

bool alarmOn = false;

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

  // Declare the Pir pin as input
  pinMode(pinPir, INPUT);
  // Declare the lights pin as an output
  pinMode(pinLights, OUTPUT);
  // Declare the LED pin as an output
  pinMode(pinLed, OUTPUT);
  // Declare the buzze pin as an output
  pinMode(pinBuzzer, OUTPUT);

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

  // Starts MQTT connection
  MQTT_connect();

  // Beging execution of the DHT11
  dht.begin();
}

void loop() { 
  if (alarmOn) {
    digitalWrite(pinLights, HIGH);
    digitalWrite(pinLed, HIGH);
    digitalWrite(pinBuzzer, HIGH);
  } 
  
  Serial.println("\n");

  // Read from our subscription queue until we run out, or
  // wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;

  // While there are any request on the subscription queue...
  while ((subscription = mqtt.readSubscription(3000))) {
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
        digitalWrite(pinLed, HIGH);
      } else if (!strcmp((char*) requestFeed.lastread, "LIGHTS_OFF")) {
        // Turn off the lights
        digitalWrite(pinLights, LOW);
        digitalWrite(pinLed, LOW);
      } else if (!strcmp((char*) requestFeed.lastread, "TEMPERATURE")) {
        // Reads the temperature from the sensor
        float temp = getTemperature();
        // Publish the temperature value to the "temperature" feed
        temperatureFeed.publish(temp);
      } else if (!strcmp((char*) requestFeed.lastread, "ALARM_ON")) {
        alarmOn = true;
      } else if (!strcmp((char*) requestFeed.lastread, "ALARM_OFF")) {
        alarmOn = false;
        digitalWrite(pinLights, LOW);
        digitalWrite(pinLed, LOW);
        digitalWrite(pinBuzzer, LOW);
      }
    }  
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
  Serial.print(" % -- ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C -- ");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C\n\n");

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
