const int led = 14;
void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  pinMode(led, OUTPUT);
}

void loop()
{
  int lectura = touchRead(T0);

  if (lectura <= 45) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  Serial.println(lectura);  // get value using T0
  delay(100);
}
