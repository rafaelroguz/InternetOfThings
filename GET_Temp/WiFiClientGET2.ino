

/*
    Este archivo envia una petición GET a un sitio web.
*/

#include <ESP8266WiFi.h>

const char *ssid = "wl-fmat-ccei"; //Red WIFI a conentar
const char *password = "";   //Contraseña de la Red WIFI
String host = "iotfirstparcial.herokuapp.com";   //Dirección del servidor

//-----------FUNCIONES--------------------
float LM35GetTemperatura()
{
  int sensorValue = analogRead(A0); //Lectura del ADC
  float millivolts = (sensorValue / 1023.0) * 3300;
  float celsius = millivolts / 10;
  return celsius;
}
//----------------------------------------

void setup() {
  Serial.begin(115200);   //inicializa puerto serial
  delay(10);
  // Inicio de la conexion a la Red WIFI
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  /* Se indica que el modulo WIFI sera cliente */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //Espera a que se conecte a Red WIFI
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
}

void loop() {
  delay(5000);  //retardo de 5 segundos
  Serial.print("Conectando a ");
  Serial.println(host);
  // Se realiza la conexion TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexion fallida");
    return;
  }
//--------obtencion  de los datos a enviar------------
  String chipid = String(ESP.getChipId());   //Identificador del modulo ESP8266
  float temperatura = LM35GetTemperatura(); //Obtiene la temperatura del sensor LM35
  Serial.println("Temperatura LM35");
  Serial.println(temperatura);
//----------------------------------------------------

  // Se establece la dirección URL para hacer el request:
  //La dirección completa de mi sitio era: "iotfirstparcial.herokuapp.com/html/maxTemp.php"
  String url = "/html/maxTemp.php?";
//----------Envio de datos--------------------
  url = url + "&chipid="+ chipid;
  url = url + "&temperatura="+String(temperatura , 2);

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  
  //Espera respuesta del servidor
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Cliente fuera de linea !");
      client.stop();
      return;
    }
  }

  // Lee la respuesta del servidor y la muestra por el puerto serie
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("cerrando conexion");
}
