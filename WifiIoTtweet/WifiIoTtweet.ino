#include <WiFi.h>
#include <IoTtweetESP32.h>

const char *userid = "";        //IoTtweet account user ID (6 digits, included zero pre-fix)
const char *key = "";     //IoTtweet registered device key in "MY IOT Garage"
const char *ssid = "";   //Your-WiFi-router-SSID
const char *password = "";    //Your-WiFi-password

float data0, data1, data2, data3;                     //Your sending data variable.
String private_tweet = "Hola Mundo - TwPriv";         //Your private tweet meassage to dashboard
String public_tweet = "Bienvenido ESP32 - TwPub";     //Your public tweet message to dashboard

IoTtweetESP32 myiot;    //naming your devices

void setup() {
  
  Serial.begin(115200);

  //Get IoTtweet Library version
  String libvers = myiot.getVersion();
  Serial.println("IoTtweet Library version : " + String(libvers));

  //Connect WiFi
  Serial.println("\nConnect wifi...");
  bool conn = myiot.begin(ssid,password);

  if(!conn){
    Serial.println("Wifi connection failed");
    } else {
      Serial.println("Wifi connected");  
    }
}

void loop() {

  //Example data generating
  data0 = random(20,80);
  data1 = random(30,70);
  data2 = random(40,60);
  data3 = random(50,55);

  //Send data from your iot to Dashboard
  String response = myiot.WriteDashboard(userid,key,data0,data1,data2,data3,private_tweet,public_tweet);
  Serial.println(response);

  Serial.println("El tweet privado es: "+ private_tweet);
  Serial.println("El tweet publico es: "+ public_tweet);
  Serial.println("\n\nLos datos a graficar son:");
  Serial.println(data0);
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
  

  //Waiting storage data on IoTtweet cloud 1 sec.
  delay(1000);

}
