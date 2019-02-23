void setup() {
  //Inicializa la comunicación serial a 9600 bits por segundo
  Serial.begin(9600);
}

void loop() {
  //Entrada analógica en el pin 0
  //int sensorValue = analogRead(A0);
  //Imprime el valor leído
  Serial.print(random(1, 100));
  Serial.print(" ");
  Serial.println(100);
  delay(1); //delay entre lecturas para estabilidad
}
