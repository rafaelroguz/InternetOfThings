#include <analogWrite.h>

const int RED = 13;
const int GREEN = 12;
const int BLUE = 14;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void setColor(int R, int G, int B) {
  //analogWrite(RED, 255 - R);
  //analogWrite(GREEN, 255 - G);
  //analogWrite(BLUE, 255 - B);

  analogWrite(RED, R);
  analogWrite(GREEN, G);
  analogWrite(BLUE, B);
}

void loop() {
  //setColor(random(127, 255), random(127, 255), random(127, 255));
  setColor(255,0,0); // Rojo
  delay(1000);

  setColor(0,255,0); // Verde
  delay(1000);

  setColor(0,0,255); // Azul
  delay(1000);

  setColor(255,255,255); // Blanco
  delay(1000);

  setColor(0,0,0); // Apagado
  delay(1000);
}
