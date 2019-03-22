#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  
  if (!SerialBT.begin("ESP32-Test")){ 
    Serial.println("An error ocurred initializing Bluetooth");
  }
}

void loop() {
  int sensorValue = analogRead(A3);
  float temperatura = ((sensorValue * 3.3) / 2048.0) / 0.01;
  SerialBT.println(temperatura);
  delay(1000);
}
