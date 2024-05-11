//librerias para pantalla
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//

#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
SoftwareSerial miBT(51, 53);   // pin 53 como RX, pin 51 como TX

#define speed_Med 22
#define Btn24 24
#define Btn26 26
#define speed_Min 28
#define speed_Max 30 
#define Btn32 32

//MOVIMIENTO TIPO TANQUE
#define TANQUE_DER_FW 35
#define TANQUE_DER_RV 49
#define TANQUE_IZQ_FW 31
#define TANQUE_IZQ_RV 33

// CRUZETA
#define CRUZE_FORWARD 45
#define CRUZE_REVERSE 41
#define CRUZETA__LEFT 47
#define CRUZETA_RIGHT 39
#define LUCES 43
#define BAILA 37
#define LAZER 29
 
#define BTN_JOYSTICK_DER A5
#define BTN_JOYSTICK_IZQ A6

int POTport = A4;
long POTvalor =  0 ;
int estadoanteriorPOTvalor =  0 ;
int velocidad  =  0;

// definiciones para Pantalla

#define ANCHO 128			// reemplaza ocurrencia de ANCHO por 128
#define ALTO 64				// reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4			// necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);	// crea objeto
String msgOled = "test";

void setup() {
  Wire.begin();					// inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);	// inicializa pantalla con direccion 0x3C
  mensajeCortoPantalla("Bienvenido");

  Serial.begin(38400);        //Inicializa puerto serie por hard
  miBT.begin(38400);    //Inicializa puerto serie por soft
  
  pinMode(TANQUE_DER_FW, INPUT_PULLUP);
  pinMode(TANQUE_DER_RV, INPUT_PULLUP);
  pinMode(TANQUE_IZQ_FW, INPUT_PULLUP);
  pinMode(TANQUE_IZQ_RV, INPUT_PULLUP);

  pinMode(CRUZE_FORWARD, INPUT_PULLUP);
  pinMode(CRUZE_REVERSE, INPUT_PULLUP);
  pinMode(CRUZETA__LEFT, INPUT_PULLUP);
  pinMode(CRUZETA_RIGHT, INPUT_PULLUP);
  pinMode(LUCES, INPUT_PULLUP);
  pinMode(BAILA, INPUT_PULLUP);
  pinMode(LAZER, INPUT_PULLUP);

  pinMode(speed_Med, INPUT_PULLUP);
  pinMode(Btn24, INPUT_PULLUP);
  pinMode(Btn26, INPUT_PULLUP);
  pinMode(speed_Min, INPUT_PULLUP);
  pinMode(speed_Max, INPUT_PULLUP);
  pinMode(Btn32, INPUT_PULLUP);

  pinMode(BTN_JOYSTICK_DER, INPUT_PULLUP);
  pinMode(BTN_JOYSTICK_IZQ, INPUT_PULLUP);
  
}

void loop() {

  if (miBT.available()) { // Si hay datos disponibles en el módulo Bluetooth
    String mensaje = miBT.readString(); // Lee el mensaje recibido
    Serial.println(mensaje); // Imprime el mensaje en el monitor serie
    mensajeCortoPantalla("Listo para operar");
  }else{
      mensajeCortoPantalla("Conectando  bluetooth");
  }

  if (digitalRead(TANQUE_DER_FW) == LOW) {  // si se presiona PULSADOR1
     int msg = 5;   miBT.write(msg);
    Serial.println("TANQUE_DER_FW");   
  }
  else if (digitalRead(TANQUE_DER_RV) == LOW) {  // si se presiona PULSADOR1
    int msg = 6;   miBT.write(msg);
    Serial.println("TANQUE_IZQ_FW");   
  }
  else if (digitalRead(TANQUE_IZQ_FW) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;   miBT.write(msg);
    Serial.println("TANQUE_IZQ_FW");   
  }
  else if (digitalRead(TANQUE_IZQ_RV) == LOW) {  // si se presiona PULSADOR1
    int msg = 8;   miBT.write(msg);
    Serial.println("TANQUE_IZQ_RV");   
  }
  else if (digitalRead(CRUZE_FORWARD) == LOW) {  // si se presiona PULSADOR1
    int msg = 1;   miBT.write(msg);
    Serial.println("CRUZE_FORWARD");   
  }
  else if (digitalRead(CRUZE_REVERSE) == LOW) {  // si se presiona PULSADOR1
    int msg = 2;   miBT.write(msg);
    Serial.println("CRUZE_REVERSE");
  }
  else if (digitalRead(CRUZETA__LEFT) == LOW) {  // si se presiona PULSADOR1
    int msg = 3;   miBT.write(msg);
    Serial.println("CRUZETA__LEFT");
  }
  else if (digitalRead(CRUZETA_RIGHT) == LOW) {  // si se presiona PULSADOR1
    int msg = 4;  miBT.write(msg);
    Serial.println("CRUZETA_RIGHT");
  }
  else if (digitalRead(LUCES) == LOW) {  // si se presiona PULSADOR1
    int msg = 15;  miBT.write(msg); mensajeCortoPantalla("LUCES");
    Serial.println("LUCES");
  }
  else if (digitalRead(BAILA) == LOW) {  // si se presiona PULSADOR1
    int msg = 9;  miBT.write(msg); mensajeCortoPantalla("BAILA");
    Serial.println("BAILA");
  }
  else if (digitalRead(LAZER) == LOW) {  // si se presiona PULSADOR1
    int msg = 10;  miBT.write(msg);     mensajeCortoPantalla("LAZER");
    Serial.println("LAZER");    
  }
  else if (digitalRead(speed_Max) == LOW) {  
    int msg = 255;  miBT.write(msg);    
    Serial.println("speed_Max");        
    mensajeCortoPantalla("Velocidad Maxima");
  }  
  else if (digitalRead(speed_Med) == LOW) {  
    int msg = 160;  miBT.write(msg);    
    Serial.println("speed_Med");       
    mensajeCortoPantalla("Velocidad Media");

    }
  else if (digitalRead(speed_Min) == LOW) { 
    int msg = 90;  miBT.write(msg);     
    Serial.println("speed_Min");       
    mensajeCortoPantalla("Velocidad Minima");

  }
  else if (digitalRead(Btn24) == LOW) {  Serial.println("Btn24");   }
  else if (digitalRead(Btn26) == LOW) {  Serial.println("Btn26");   }  
  else if (digitalRead(Btn32) == LOW) {  Serial.println("Btn32");   }
  else if (digitalRead(BTN_JOYSTICK_DER) == LOW) {  Serial.println("BTN_JOYSTICK_DER");   }
  else if (digitalRead(BTN_JOYSTICK_IZQ) == LOW) {  Serial.println("BTN_JOYSTICK_IZQ");   }
  else {  
    int msg = 0;
    miBT.write(msg);
  } 
   
  delay(50);

}

void mensajeCortoPantalla(String msgOled){
  oled.clearDisplay();			// limpia pantalla			
  oled.setCursor(0, 0);		// ubica cursor en coordenadas 28,34
  oled.setTextSize(2);			// establece tamano de texto en 2
  oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
  oled.print(msgOled);			// escribe texto
  oled.display();			// muestra en pantalla todo lo establecido anteriormente
}
