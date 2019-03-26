//#include "BluetoothSerial.h"

//BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  
  //if (!SerialBT.begin("ESP32-Test")){ 
    //Serial.println("An error ocurred initializing Bluetooth");
  //}
}

void loop() {
  int sensorValue = analogRead(A0);
  double temperatura = ((sensorValue * 3.3) / 2048.0) / 0.01;
  Serial.println(temperatura);
  delay(1000);
}
