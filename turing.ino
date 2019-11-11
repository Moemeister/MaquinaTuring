#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//txd 7 rxd 10 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial ModuloHC05 (7, 10);
const int numRows = 2;
const int numCols = 16;

char arregloi[] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char arreglo[16];
bool leyendo=true;
int longitud = 0;
int mitad1 = 0;
int mitad = 0;
int pointer = 0;
int automataB = 8;
int automataB2 = 9;
int indice = 0;
int first = 0;
int counterP = 0;
int estado = 0;
int i = 0;
int limit = 0;
int automata = 0;
int indice2 = 1;
char caracter;

void setup() {
  lcd.begin(numCols, numRows);
  pinMode(automataB, INPUT);
   ModuloHC05.begin(9600);
  Serial.begin(9600);
}


void loop() {

  if(leyendo){
      if (ModuloHC05.available()){     
            caracter= ModuloHC05.read();  
            Serial.write(caracter);
            arregloi[indice2]=caracter;
            if(caracter=='$'){
                //arreglo[0]=' ';
                for(int a=0;a<=indice2;a++){
                    arreglo[a]=arregloi[a];
                    longitud=a;
                    //Serial.print(longitud);
                  }
                  mitad1 = numCols-longitud;
                  mitad = mitad1/2;
                  pointer = mitad1/2;
                  limit = longitud;
                  leyendo=false;
              }
              indice2++;
              if(indice2==18){
                  indice2=17;
                }
        }
        
        
    }else{
  if(digitalRead(automataB)==HIGH){
    automata=1;
  }
  if(digitalRead(automataB2)==HIGH){
    automata=2;
  }
  if(estado!=2 && automata==1){  
    llenarLCD();
      leerArreglo();
      calculos();
      first=1;
   
    leerArreglo();
  
    printEstado();
    mueveCursor();
  
    leerArreglo();
  }else if(estado==2 &&automata==1){
    lcd.setCursor(3,1);
    lcd.print("Aceptado!");
  }
  if(estado!=2 && automata==2){  
  llenarLCD();
    leerArreglo();
    calculos2();
   
    leerArreglo();
  
    printEstado();
    mueveCursor();
  
    leerArreglo();
  }else if(estado==2 &&automata==2){
    lcd.setCursor(3,1);
    lcd.print("Aceptado!");
  }
  }
}


void llenarLCD(){
  for (int thisCol = 0; thisCol < mitad; thisCol++) {
        lcd.setCursor(thisCol, 0);
        lcd.write('*');
        delay(200);
      }
  for (int thisCol = mitad+longitud; thisCol <= numCols; thisCol++) {
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
                    i--;
                }
        }
        else if(estado == 1){
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

void calculos2(){
  if(i <= limit){
        char x = arreglo[i];
      lcd.setCursor(i+mitad,0);
      lcd.write('_');
      delay(100);
      Serial.print(i);
        if(estado == 0){
          if(x== ' '){
            i++;
          }
                if(x == '1'){
                    estado = 0;
                    arreglo[i]='0';
                    i++;
                }else if(x == '0'){
                  estado = 0;
                    arreglo[i]='1';
                    i++;
                }else if(x == '$'){
                    estado = 1;
                    i--;
                }
        }
        else if(estado == 1){
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
