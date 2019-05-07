#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


//const char* ssid = "wl-fmat-ccei";
//const char* password = "";

const char* ssid = "izzi-cifuentes";
const char* password =  "22709946";

const char* brokerUser = "irving.aacg@gmail.com";
const char* brokerPass = "dd1e1f9f";
const char* broker = "mqtt.dioty.co";

const char* outTopic = "/irving.aacg@gmail.com/out";
const char* inTopic = "/irving.aacg@gmail.com/in";
long currentTime, lastTime;
int cont = 0;
char messages[50];

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect()
{
  while(!client.connected())
  {
    Serial.print("\nConnecting to ");
    Serial.println(broker);
    if(client.connect("micliente", brokerUser, brokerPass))
    {
      Serial.print("\nConnected to ");
      Serial.println(broker);
      client.subscribe(inTopic);
    }
    else
    {
      Serial.println("\nTriying connect again");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  String s = "";
  Serial.print("Received messages: ");
  Serial.println(topic);
  for(int i=0;i<length; i++)
  {
    Serial.print((char) payload[i]);
    s = s + (char) payload[i];
  }
  Serial.println();
  Serial.println("cadena:");
  Serial.println(s);
  
  if ((char) payload[0] == 'f') {
    digitalWrite(23, LOW);   

    Serial.println("LED apagado");
    
  } if((char) payload[0] == 't') {
    digitalWrite(23, HIGH);  
    Serial.println("LED encendido");
  }


  
  Serial.println();
}

void setup() {
  // put your setup code here, to run once: 

  
  pinMode(23, OUTPUT);
  
  digitalWrite(23, LOW); 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WIFI..");
  }
  Serial.println("Conectado a Internet");



  client.setServer(broker,1883);

  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(!client.connected())
  {
    reconnect();
  }
  client.loop();

  currentTime = millis();
  if(currentTime - lastTime > 2000)
  {
    cont++;
    snprintf(messages, 75, "cont: %1d", cont);
    Serial.print("Sending messages: ");
    Serial.println(messages);
    client.publish(outTopic, messages);
    lastTime = millis();
  }
}
