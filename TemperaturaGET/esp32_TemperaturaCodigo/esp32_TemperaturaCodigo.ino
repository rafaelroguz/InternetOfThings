#include <WiFi.h>
#include <HTTPClient.h>
 
//const char* ssid = "wl-fmat-ccei";
//const char* pass =  "";
const char* ssid = "RODRIGUEZ";
const char* pass =  "{IZZI:m5s2n9bz}";
String host = "https://temperaturaesp32.herokuapp.com/UpdateDB.php?temp="; 

float getTemperatura() {
  int sensorValue = analogRead(A0);
  double temperatura = ((sensorValue * 3.3) / 2048.0) / 0.01;
  return temperatura;
}

void setup() { 
  Serial.begin(9600);
  delay(1000);
  WiFi.begin(ssid, pass);
  Serial.println("Conectando a WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a la red ");
  Serial.println(ssid);
}
 
void loop() {
  //float temperatura = getTemperatura();
  float temperatura = random(25, 30);
  
  Serial.print("ESP32 dice: La temperatura es de ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    String url = "";
    
    url = host + temperatura;
    http.begin(url);
     
    int httpCode = http.GET();
 
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
 
    http.end();
  } else {
    Serial.println("¡Se ha perdido la conexión Wi-Fi!");
  }
 
  delay(2000);
}
