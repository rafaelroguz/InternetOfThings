#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "wl-fmat-ccei";
const char* password =  "";
String Host = "https://api.thingspeak.com/update?api_key=EQGUTQP2N5E0DO8W";  // Aquí colocar nuestra API Keys
void setup() {
 
  Serial.begin(115200);
  delay(4000);
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


    int numAleatorio = random(100);
    url = Host + "&field1="+numAleatorio; 

    
    
    http.begin(url); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(1000);
 
}
