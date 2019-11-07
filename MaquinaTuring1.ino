#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;
const int numCols = 16;

char arreglo[]={' ','1','1','1','1','1','0','$'};
int longitud = sizeof(arreglo);
int mitad1 = numCols-longitud;
int mitad = mitad1/2;
int pointer = mitad1/2;
int pointerPin = 8;
int indice = 0;
int first = 0;
int counterP = 0;
int estado = 0;
int i = 0;
int limit = strlen(arreglo);

void setup() {
  lcd.begin(numCols, numRows);
  pinMode(pointerPin, INPUT);
}


void loop() {
  if(estado!=2){  
  	//if(first ==0){    
		llenarLCD();
  		leerArreglo();
    	calculos();
    	first=1;
  	//}
   
  	leerArreglo();
  
  	printEstado();
  	mueveCursor();
  
  	leerArreglo();
  }else{
  	lcd.setCursor(3,1);
  	lcd.print("Aceptado!");
  }
}


void llenarLCD(){
  for (int thisCol = 0; thisCol < mitad; thisCol++) {
        lcd.setCursor(thisCol, 0);
        lcd.write('*');
        delay(200);
      }
  for (int thisCol = mitad+longitud-1; thisCol <= numCols; thisCol++) {
        lcd.setCursor(thisCol, 0);
        lcd.write('*');
        delay(200);
      }
}

void leerArreglo(){
	for(int thisChar=mitad; thisChar<(longitud+mitad); thisChar++){
    lcd.setCursor(thisChar,0);
      if(arreglo[indice]!='$'){
      	lcd.write(arreglo[indice]);
      }
    indice++;
    if(indice==(longitud)){
      indice=0;
    }
  }
}

void mueveCursor(){
  if(counterP < 1){
    counterP++;
    if(counterP==1){
    	pointer++;
      if(pointer==mitad+longitud){
      	pointer--;
      }
      counterP=0;
    }
  }
}

void calculos(){
  if(i <= limit){
        char x = arreglo[i];
    	lcd.setCursor(i+mitad,0);
  		lcd.write('_');
  		delay(100);
        if(estado == 0){
                if(x == '1' || x == '0'||x == ' '){
                    estado = 0;
                    i++;
                }else if(x == '$'){
                    estado = 1;
                }
        }
        else if(estado == 1){
          if(i >= limit-2){
                    i--;
          }
                //printf("n: %d\n",i);
                if (x == '1' ){
                    arreglo[i] = '0';
                  	leerArreglo();
                  	
                    i--;
                }else if(x == '0' || x==' '){
                    arreglo[i] = '1';
                  	leerArreglo();
                  	estado=2;
                }
        }

    }
  
  
}

void printEstado(){
	lcd.setCursor(3,1);
  	lcd.print("Estado q");
  	lcd.setCursor(11,1);
  	lcd.print(estado);
}
