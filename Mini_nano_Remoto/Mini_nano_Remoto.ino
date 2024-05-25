//librerias para pantalla
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//libreria bluetooth
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
SoftwareSerial mySerial(10, 11);   // pin 11 como RX, pin 10 como TX
int databt = 0;      // variable para almacenar caracter recibido por bluetooth


// bucle sin dealy()
#define BOTON0 0
#define BOTON1 1
#define BOTON2 2
#define BOTON7 7
#define BOTON13 13

// CRUZETA
#define CRUZE_FORWARD 6
#define CRUZE_REVERSE 9
#define CRUZETA__LEFT 12
#define CRUZETA_RIGHT 8
#define LUCES 5
#define BAILA 3
#define LAZER 4

#define BTN_JOYSTICK A1
int POTport = A0;
long POTvalor =  0 ;
int estadoanteriorPOTvalor =  0 ;
int velocidad  =  0;

// Pantalla

#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto


int led = 7;   // Led conectado en el pin D7

//*********** antidelay
bool bucle_activado = false; // Estado de un bucle (activado o desactivado)
unsigned long actual = 0;  //almacena un número entero muy largo
unsigned long anterior = 0;
bool estado_led = LOW; //led en estado bajo.
int timedelay = 100;



void setup() {

  Wire.begin();					// inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();      // limpia pantalla

  Serial.begin(38400);        //Inicializa puerto serie por hard
  mySerial.begin(38400);    //Inicializa puerto serie por soft

  pinMode(CRUZE_FORWARD, INPUT_PULLUP);
  pinMode(CRUZE_REVERSE, INPUT_PULLUP);
  pinMode(CRUZETA__LEFT, INPUT_PULLUP);
  pinMode(CRUZETA_RIGHT, INPUT_PULLUP);
  pinMode(LUCES, INPUT_PULLUP);
  pinMode(BAILA, INPUT_PULLUP);
  pinMode(LAZER, INPUT_PULLUP);

  pinMode(BTN_JOYSTICK, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  //*********** antidelay
  anterior = millis();
}


void loop() {

  //  if (mySerial.available()) { // Si hay datos disponibles en el módulo Bluetooth
  //    //mensajeCortoPantalla("CONECTADO");
  //    //String mensaje = mySerial.readString(); // Lee el mensaje recibido
  //     databt = mySerial.read();   // almacena en databt el caracter recibido desde modulo
  //    Serial.println("CONECTADO");
  //  }else{    Serial.println("NO CONECTADO");
  //
  //     //mensajeCortoPantalla("Conectando  bluetooth");
  //  }
  //
  //test Code int msg = 2; mySerial.write(msg); int msgspeed = 255;  mySerial.write(msgspeed);

  //*********** antidelay

  if (!digitalRead(CRUZE_FORWARD)) {
  }

  if (digitalRead(CRUZE_FORWARD) == LOW) {  // si se presiona PULSADOR1
    int msg = 1;   mySerial.write(msg);
    mensajeCortoPantalla("ADELANTE");
    Serial.println("CRUZE_FORWARD");
  }
  else if (digitalRead(CRUZE_REVERSE) == LOW) {  // si se presiona PULSADOR1
    int msg = 2;   mySerial.write(msg);
    mensajeCortoPantalla("ATRAS");
    Serial.println("CRUZE_REVERSE");

  }
  else if (digitalRead(CRUZETA__LEFT) == LOW) {  // si se presiona PULSADOR1
    int msg = 3;   mySerial.write(msg);
    mensajeCortoPantalla("DERECHA");
    Serial.println("CRUZETA__LEFT");

  }
  else if (digitalRead(CRUZETA_RIGHT) == LOW) {  // si se presiona PULSADOR1
    int msg = 4;  mySerial.write(msg);
    mensajeCortoPantalla("IZQUIERDA");
    Serial.println("CRUZETA_RIGHT");

  }
  else if (digitalRead(LUCES) == LOW) {  // si se presiona PULSADOR1
    int msg = 15;  mySerial.write(msg);
    mensajeCortoPantalla("LUCES");
    Serial.println("LUCES");
  }
  else if (digitalRead(BAILA) == LOW) {  // si se presiona PULSADOR1
    int msg = 9;  mySerial.write(msg);
    mensajeCortoPantalla("BAILA");
    Serial.println("BAILA");
  }
  else if (digitalRead(LAZER) == LOW) {  // si se presiona PULSADOR1
    int msg = 10;  mySerial.write(msg);
    mensajeCortoPantalla("LAZER");
    Serial.println("LAZER");
  }

  else if (digitalRead(BTN_JOYSTICK) == LOW) {
    Serial.println("BTN_JOYSTICK");
  }
  else {
    int msg = 0;
    mySerial.write(msg);
  }
  oled.clearDisplay();      // limpia pantalla


  //*********** antidelay
  bucle_activado = true;
  actual = millis(); //para obtener el valor anterior justo en el momento que arranca el código
  if (actual - anterior > timedelay)
  {
    anterior = millis(); // o escribir: anterior + 1000;
    if (bucle_activado) {
      estado_led = !estado_led;
      digitalWrite (led, estado_led);
    }
  }
  //*********** antidelay

}

void mensajeCortoPantalla(String frase) {
  oled.clearDisplay();      // limpia pantalla
  oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(3);      // establece tamano de texto en 1
  oled.print(frase);  // escribe en pantalla el texto
  oled.setCursor (10, 30);    // ubica cursor en coordenas 10,30
  oled.setTextSize(2);      // establece tamano de texto en 2
  oled.display();     // muestra en pantalla todo lo establecido anteriormente
}
