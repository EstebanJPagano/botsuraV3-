
/* include library */
#include <Servo.h>           // Add Servo library
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales


SoftwareSerial miBT(53, 51);   // pin 19 como RX, pin 18 como TX

// ----------- Puenteh
#define PWM1 5
#define AIN1 7
#define AIN2 8

#define PWM2 6
#define BIN1 4
#define BIN2 9

#define EN1 A0
#define EN2 A1


int speedCar = (unsigned char)1023;   // variable para almacenar valor de velocidad
int speedMAX = (unsigned char)1023;  // variable para almacenar valor de velocidad
int speedMED = (unsigned char)800;     // variable para almacenar valor de velocidad
int speedMIN = (unsigned char)600;      // variable para almacenar valor de velocidad
int speedOff = 0 ;
char dato = 0;      // variable para almacenar caracter recibido

// ---------- Servo
Servo myservoH;               // Define any servo name
int contador;
int powerServ = 30;



// ----------- definir led
int PinLED0 = 45; //blanco adelante
int PinLED1 = 47; //blanco adelante
int PinLED2 = 43; //traseras
int PinLED3 = 49; //Sierna


// ---------- Sensor infrarrojo de obstaculos.
int IR = 33;
int valorSensor;

void setup(){
  
  miBT.begin(38400);
  Serial.begin(38400);

  // Monster
  pinMode(BIN1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN2,OUTPUT);
  
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
   
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A5,INPUT);
  

 //Servos
  myservoH.attach (2);          // Define the servo signal pins
  pinMode(powerServ, OUTPUT);   // IN1 como salida  
  digitalWrite(powerServ, HIGH);
   
  // LED  
  pinMode(PinLED0, OUTPUT);              
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLED3, OUTPUT);
  // Sensor IR obstaculos
  pinMode(IR, INPUT);  
}

void loop(){
   //------------Bluetooth
  if (miBT.available()){     // si hay informacion disponible desde modulo
    dato = miBT.read();   // almacena en dato el caracter recibido desde modulo
    Serial.println("dato");
    Serial.println(dato);
    Serial.write(dato);                       //Sacarlo a la terminal
   
      
      if(dato == '1') { MotorForward();
      }
      else if(dato == '3') {MotorBackward();}
      else if(dato == '4') {TurnLeft();}
      else if(dato == '2') {TurnRight();}
      else if(dato == '0') {MotorStop(); }  //motor stop
      
      else if(dato == 'a') { SetSpeedCarMax(); }
      else if(dato == 'b') { SetSpeedCarUp();  }
      else if(dato == 'c') { SetSpeedCarDown(); }
      
      else if(dato == 'd') { goLuces(); }
      else if(dato == 'e') { goLucesOff(); }
      else if(dato == 'f') { led_blink(); }
    
      else if(dato == 'h') { rotarCabeza_H_I(); }//rotar horizontal izquierda
      else if(dato == 'i') { rotarCabeza_H_D(); } //rotar horizontal derecha
      else if(dato == 'j') { rotarCabeza_H_90(); } //rotar horizontal derecha
      else if(dato == 'k') { goLucesColor(); } 
      else if(dato == 'l') { goLucesOffColor(); }
  }
  
    /*// sensor ir    
    int value = 0;
    value = digitalRead(IR);
    
    if (value == LOW){
     Serial.println ("si");
     MotorStop();
    }*/
     delay(500);
}


// Funciones de motores
/* FORWARD */
void MotorForward(){
  goLuces();
  goLucesColorSirena();
  
  analogWrite(PWM1,speedCar); //Speed control of Motor A
  analogWrite(PWM2,speedCar); //Speed control of Motor B
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
}

/* BACKWARD */
void MotorBackward(){
  
  goLucesColor();
  goLucesColorSirena();
  
  analogWrite(PWM1,speedCar); //Speed control of Motor A
  analogWrite(PWM2,speedCar); //Speed control of Motor B
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);  
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
}

/* TURN RIGHT */
void TurnRight(){
  goLucesColor();
  analogWrite(PWM1,speedCar); //Speed control of Motor A
  analogWrite(PWM2,speedCar); //Speed control of Motor B
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);  
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  
}

/* TURN LEFT */
void TurnLeft(){
  goLucesColor();  
  analogWrite(PWM1,speedCar); //Speed control of Motor A
  analogWrite(PWM2,speedCar); //Speed control of Motor B
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);  
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
}

void MotorStop(){
  
  analogWrite(PWM1, speedOff);    // deshabilita motor A
  analogWrite(PWM2, speedOff);    // deshabilita motor B
  
  goLucesColor();
  goLucesColorSirena();
  delay(90); 
  goLucesOff();
}

//  -----------------------  SPEED  -----------------------
void SetSpeedCarMax(){
  speedCar = speedMAX;
  Serial.print("speedCar "+ speedCar);
  delay(90);  
}



void SetSpeedCarUp(){
  speedCar = speedMED;
  Serial.print("speedCar s"+ speedCar);
  delay(90);  
}


void SetSpeedCarDown(){
  speedCar = speedMIN;
  delay(90);  
}

//--------------------- SERVO --------------------- 

void rotarCabeza_H_I(){
  if(contador == 0){ contador = 90; }
  contador = contador + 25;               //Incrementa el contador
  delay (300);           // Retardo
  myservoH.write(contador); 
 }
 
void rotarCabeza_H_D(){ 
 if(contador == 0){ contador = 90;  }
 contador= contador - 25;               //Incrementa el contador
 delay (300);           // Retardo
 myservoH.write(contador);
}

void rotarCabeza_H_90(){ myservoH.write(90); }

// ----------------- LUCES  -----------------
void led_blink(){
 int var = 0;
  while (var < 3) {
    digitalWrite(PinLED0, HIGH);
    delay(90); 
    digitalWrite(PinLED1, HIGH);
    delay(90);
    digitalWrite(PinLED2, HIGH);
    delay(90);
    digitalWrite(PinLED3, HIGH);
    delay(90);

    digitalWrite(PinLED0, LOW);
    delay(90); 
    digitalWrite(PinLED1, LOW);
    delay(90);
    digitalWrite(PinLED2, LOW);
    delay(90); 
    digitalWrite(PinLED3, LOW);
    delay(90); 
    
    var ++;
  }
}

void goLuces(){ 
  digitalWrite(PinLED0, HIGH);
  digitalWrite(PinLED1, HIGH);
}

void goLucesOff(){ 
  digitalWrite(PinLED0, LOW);
  digitalWrite(PinLED1, LOW);  
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED3, LOW);  
}

void goLucesColor(){ 
  digitalWrite(PinLED2, HIGH);
}

void goLucesColorSirena(){ 
  digitalWrite(PinLED3, HIGH);
}

void goLucesOffColor(){ 
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED3, LOW);
}
