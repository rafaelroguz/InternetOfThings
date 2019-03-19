void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float temperatura = ((sensorValue * 5.0) / 1024.0) / 0.01;
  Serial.println(temperatura);
  delay(1000);
}
