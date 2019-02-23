void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0); 
  double voltaje = (sensorValue * 3.3) / 2048;
  double temperatura = voltaje/0.01;  
  Serial.println(temperatura);
  delay(1000);
}
