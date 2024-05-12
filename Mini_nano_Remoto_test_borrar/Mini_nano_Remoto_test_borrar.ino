//librerias para pantalla
#include <SPI.h>
#include <Wire.h>

#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
SoftwareSerial miBT(10, 11);   // pin 11 como RX, pin 10 como TX

#define BOTON0 0
#define BOTON1 1
#define BOTON2 2
#define BOTON3 3
#define BOTON4 4
#define BOTON5 5
#define BOTON6 6
#define BOTON7 7
#define BOTON8 8
#define BOTON9 9
#define BOTON12 12
#define BOTON13 13



void setup() {
  Wire.begin();					// inicializa bus I2C
  

  Serial.begin(38400);        //Inicializa puerto serie por hard
  miBT.begin(38400);    //Inicializa puerto serie por soft
  
   pinMode(BOTON0, INPUT_PULLUP);
   pinMode(BOTON1, INPUT_PULLUP);
   pinMode(BOTON2, INPUT_PULLUP);
   pinMode(BOTON3, INPUT_PULLUP);
   pinMode(BOTON4, INPUT_PULLUP);
   pinMode(BOTON5, INPUT_PULLUP);
   pinMode(BOTON6, INPUT_PULLUP);
   pinMode(BOTON7, INPUT_PULLUP);
   pinMode(BOTON8, INPUT_PULLUP);
   pinMode(BOTON9, INPUT_PULLUP);
   pinMode(BOTON12, INPUT_PULLUP);
   pinMode(BOTON13, INPUT_PULLUP);

}

void loop() {

  if (miBT.available()) { // Si hay datos disponibles en el módulo Bluetooth
    String mensaje = miBT.readString(); // Lee el mensaje recibido
    Serial.println(mensaje); // Imprime el mensaje en el monitor serie
  }else{
      // Serial.println("Conectando  bluetooth");
  }    

  if (digitalRead(BOTON0) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("TANQUE_IZQ_FW");   
  }
  
  if (digitalRead(BOTON1) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON1");   
  }
  
  if (digitalRead(BOTON2) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON2");   
  }
  
  if (digitalRead(BOTON3) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON3");   
  }
  
  if (digitalRead(BOTON4) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON4");   
  }
  
  if (digitalRead(BOTON5) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON5");   
  }
  
  if (digitalRead(BOTON6) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON6");   
  }
  
  if (digitalRead(BOTON7) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON7");   
  }
  
  if (digitalRead(BOTON8) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON8");   
  }
  
  if (digitalRead(BOTON9) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON9");   
  }
  
  if (digitalRead(BOTON12) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("BOTON12");   
  }
  
  

  delay(50);

}
