int pin = 34;
int led = 25;
 
void setup()
{
  pinMode(pin,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  //digitalWrite(led, LOW);
}
 
void loop()
{
  float dato = digitalRead(pin);
  Serial.println(dato);
  if(dato == HIGH){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
 
  delay(500);
}
