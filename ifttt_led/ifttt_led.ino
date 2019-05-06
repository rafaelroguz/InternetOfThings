#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "WiFi.h"
#include <DHT.h>

//#define WIFI_SSID "Roguz"
//#define WIFI_PASS "WIFIh4anw8"

#define WIFI_SSID "RODRIGUEZ"
#define WIFI_PASS "{IZZI:m5s2n9bz}"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "rafaelroguz"
#define MQTT_PASS "1cee6e836738402582666a4a98ed154c"

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int pinLed = 13;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe request = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Request");
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/Temperature");

void setup() {
  Serial.begin(9600);
  Serial.print("\n\nConnecting Wifi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Conected to WIFI");

  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  
  //Subscribe to the ToggleLights topic
  mqtt.subscribe(&request);

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
  
  dht.begin();
}

void loop() {
  //Connect/Reconnect to MQTT
  MQTT_connect();

  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  
  while ((subscription = mqtt.readSubscription(5000))) {
    //If we're in here, a subscription updated...
    if (subscription == &request) {
      //Print the new value to the serial monitor
      //Serial.print("Lights: ");
      Serial.println((char*) request.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) request.lastread, "LightsON")) {
        digitalWrite(pinLed, HIGH);
        //LightsStatus.publish("LightsON");
      } else if (!strcmp((char*) request.lastread, "LightsOFF")) {
        digitalWrite(pinLed, LOW);
        //LightsStatus.publish("LightsOFF");
      } else if (!strcmp((char*) request.lastread, "TEMPERATURE")) {
        //LightsStatus.publish("ERROR");
        float temp = readTemperature();
        Temperature.publish(temp);
      }
    }
  }
}

float readTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return 0.0;
  }
 
  float hic = dht.computeHeatIndex(t, h, false);
 
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

void MQTT_connect() {
  // Stop if already connected
  if (mqtt.connected() && mqtt.ping()) {
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  Serial.print("Connecting to MQTT...");
  uint8_t retries = 3;

  // connect will return 0 for connected
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
