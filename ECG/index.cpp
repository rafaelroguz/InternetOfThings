#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main();
void readData(float electro[], int segundos, int frecuencia);

int main() {
   string cadena;
   int segundos = 0;
   int lineCounter = 0;
   int frecuencia = 2000;
   // Abre un fichero de entrada
   ifstream fe("ECGS.txt"); 

   cout << "Segundos a evaluar: ";
   cin >> segundos;
   float electroSegment[segundos*frecuencia];

    while(!fe.eof()) {
      lineCounter++;
      if (lineCounter > (segundos*frecuencia)) {
        break;
      }
      float muestra = strtof((cadena).c_str(),0);
      float muestraABS = (muestra);
      electroSegment[lineCounter - 1] = muestraABS;
      fe >> cadena;    
   }
   
   fe.close();
   readData(electroSegment, segundos, frecuencia);
   return 0;
}

void readData (float electro[], int segundos, int frecuencia) {		
	int microsegundo = frecuencia / 100;
	int subidas = 0;
	int bajadas = 0;
	int latido = 0;
	for (int i = 0; i < (segundos*frecuencia); i++){
		if(electro[i] < electro[i+1]){
			subidas++;
			bajadas = 0;
		}
		if(electro[i] > electro[i+1]){
			bajadas++;
			subidas = 0;
		}
		if(subidas > microsegundo){
			latido++;
		}
	}
	int pulsoCardiaco = ((latido/2) * 60)/segundos;
	cout << pulsoCardiaco;
}

