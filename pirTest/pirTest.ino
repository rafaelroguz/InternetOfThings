int pinPir = 18;
int pinBuzzer = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinPir, INPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  if (digitalRead(pinPir)) {
    digitalWrite(pinBuzzer, HIGH);
  } else {
    digitalWrite(pinBuzzer, LOW);
  }
}
