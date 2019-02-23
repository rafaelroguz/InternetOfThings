int const LED = 13;
int option;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    option = Serial.read();

    if (option == 'a') {
      digitalWrite(LED, LOW);
      Serial.println("OFF");
    }

    if (option == 'b') {
      digitalWrite(LED, HIGH);
      Serial.println("ON");
    }
  }
}
