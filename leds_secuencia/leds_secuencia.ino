int const totalLEDs = 8;

//Arreglo que contiene el número de pin que se usa para cada LED
int LEDs[8] = {32, 33, 25, 26, 27, 14, 12, 13};

void setup() {
  int i = 0;

  //Inicializamos cada LED como salida
  for (i = 0; i < totalLEDs; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
}

//Código de prueba del funcionamiento de los LEDs
/*
void turnOnAllLEDs() {
  int i = 0;

  for (i = 0; i < totalLEDs; i++) {
    digitalWrite(LEDs[i], HIGH);
  }
}

void turnOffAllLEDs() {
  int i = 0;

  for (i = 0; i < totalLEDs; i++) {
    digitalWrite(LEDs[i], LOW);
  }
}

void testLEDs() {
  turnOnAllLEDs();
  delay(1000);
  turnOffAllLEDs();
  delay(1000);
}
*/

//Maneja la secuencia de encendido y apagado, ida y vuelta, de los LEDs
void secuencia(int espera) {
  int i = 0;

  //Enciende y apaga los LEDs del 1 al 7
  for (i = 0; i < totalLEDs-1; i++) {
    digitalWrite(LEDs[i], HIGH);
    delay(espera);
    digitalWrite(LEDs[i], LOW);
  }

  //Enciende y apaga los LEDs del 8 al 2
  for (i = totalLEDs-1; i > 0; i--) {
    digitalWrite(LEDs[i], HIGH);
    delay(espera);
    digitalWrite(LEDs[i], LOW);
  }
}

void loop() {
  //testLEDs();

  int i = 0;
  int iteracionesTotales = 3;
  int espera = 1000;
  //int reduccionEspera = 300;

  //Realizamos 4 iteraciones, decrementando el tiempo de espera en las últimas 3
  for (i = 0; i <= iteracionesTotales; i++) {
    secuencia(espera); 
    //espera = espera - reduccionEspera;
    espera = espera / 2;
  }
}
