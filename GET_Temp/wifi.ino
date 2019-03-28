#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "wl-fmat-ccei";
const char* password =  "";
String Host = "http://192.168.0.0:3000"; 

double getTemperatura()
{
  int sensorValue = analogRead(A0);
  double temperatura = ((sensorValue * 3.3) / 2048.0) / 0.01;
  return temperatura;
}

void setup() {
  Serial.begin(115200);
  delay(4000);
  WiFi.mode(WIFI_STA);
  WiFi.begin("wl-fmat-ccei", "");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
}
 
void loop() {

  int valor = random(0, 100);
  Serial.println("valor:"+valor);
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    String url = "";
    double temp = getTemperatura();
    
    url = Host;
    http.begin(url); //Specify the URL
    
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
        Serial.println(temp)
        // String payload = http.getString();
        // Serial.println(httpCode);
        // Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(1000);
}
