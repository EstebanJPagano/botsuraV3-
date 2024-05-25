// bluetooth
#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
SoftwareSerial miBT(53, 51);   // pin 53 como RX, pin 51 como TX
int databt = 0;      // variable para almacenar caracter recibido por bluetooth

// ----------- definir led
int PinLED1 = 22; //Sierna
int PinLED2 = 23;
int PinLED3 = 24;
int PinLED4 = 25; //Sierna
int PinLED5 = 26; // adelante izquierda
int PinLED6 = 27; //adelante derecha

// ---------- Sensor infrarrojo de obstaculos.
int IR = 33;
int valorSensor;

// lazer
int LAZER = 48;
// Monster
#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

short usSpeed = 255;  //default motor speed
unsigned short usMotor_Status = BRAKE;

void setup() {

  miBT.begin(38400);
  Serial.begin(38400);

  // LED
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLED3, OUTPUT);
  pinMode(PinLED4, OUTPUT);
  pinMode(PinLED5, OUTPUT);
  pinMode(PinLED6, OUTPUT);
  
  // LAZER  
  pinMode(LAZER, OUTPUT);


  // Sensor IR obstaculos
  pinMode(IR, INPUT);

  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);

  Serial.println("Begin motor control");
  //Serial.println(); //Print function list for user selection
}

void loop() {
  
  //------------Bluetooth
  if (miBT.available()) {    // si hay informacion disponible desde modulo
    databt = miBT.read();   // almacena en databt el caracter recibido desde modulo
    Serial.println(databt);

   // goLucesColorSirena();

    if (databt == 0) {
      Stop();
      goLucesOff();
    }
    else if (databt == 4) {
      Forward();
      goLucesAdelante();
    }
    else if (databt == 2) {
      Reverse();
      goLucesReversa();
    }
    else if (databt == 1) {
      Left();
      goLucesIzquierda();
    }
    else if (databt == 3) {
      Right();
      goLucesDerecha();
    }

    else if (databt == 6) {
      derForward();
    }
    else if (databt == 5) {
      derReverse();
    }
    else if (databt == 8) {
      izqForward();
    }
    else if (databt == 7) {
      izqReverse();
    }

    else if (databt == 9) {
      danceDance();
    }
    else if (databt > 30 ) {
      SetSpeedCar(databt);
    }
    else if (databt == 13) {
      goLuces();
    }
    else if (databt == 14) {
      goLucesOff();
    }
    else if (databt == 15) {
      led_blink();     

    }
    else if (databt == 16) {
      goLucesColor();
    }
    else if (databt == 17) {
      goLucesOffColor();
    }
    else if (databt == 18) {
       digitalWrite(LAZER, HIGH);

    }
    else {
      Stop();
      goLucesOff();
    }

    //else { Serial.println("Invalid option entered."); }

  }

}


void derForward() {
  Serial.println("derForward");
  motorGo(MOTOR_2, CW, 255);
  motorGo(MOTOR_1, CW, 100);
}
void derReverse() {
  Serial.println("derReverse");
  motorGo(MOTOR_2, CCW, 255);
  motorGo(MOTOR_1, CCW, 100);
}
void izqForward() {
  Serial.println("izqForward");
  motorGo(MOTOR_1, CW, 255);
  motorGo(MOTOR_2, CW, 100);
}
void izqReverse() {
  Serial.println("izqReverse");
  motorGo(MOTOR_1, CCW, 255);
  motorGo(MOTOR_2, CCW, 100);
}

void Forward() {
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
}

void Reverse() {
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
}


void Left() {
  Serial.println("Left");
  motorGo(MOTOR_1, CW, usSpeed);
  motorGo(MOTOR_2, CCW, usSpeed);
}


void Right() {
  Serial.println("Right");
  motorGo(MOTOR_1, CCW, usSpeed);
  motorGo(MOTOR_2, CW, usSpeed);
}


void Stop() {
  //Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) {        //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);

  if (motor == MOTOR_1) {
    if (direct == CW) {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if (direct == CCW) {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    else {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_1, pwm);
  }
  else if (motor == MOTOR_2) {
    if (direct == CW) {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if (direct == CCW) {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    else {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);
    }
    analogWrite(PWM_MOTOR_2, pwm);
  }
}
//  -----------------------  SPEED  -----------------------
int SetSpeedCar(int speed) {
  usSpeed = speed;
  Serial.print("speedCar " + usSpeed);
  delay(90);
}



// ----------------- LUCES  -----------------
void led_blink() {
  int var = 0;

  digitalWrite(PinLED1, HIGH);
  delay(90);
  digitalWrite(PinLED2, HIGH);
  delay(90);
  digitalWrite(PinLED3, HIGH);
  delay(90);
  digitalWrite(PinLED4, HIGH);
  delay(90);
  digitalWrite(PinLED5, HIGH);
  delay(90);
  digitalWrite(PinLED6, HIGH);
  delay(90);

  digitalWrite(PinLED1, LOW);
  delay(90);
  digitalWrite(PinLED2, LOW);
  delay(90);
  digitalWrite(PinLED3, LOW);
  delay(90);
  digitalWrite(PinLED4, LOW);
  delay(90);
  digitalWrite(PinLED5, LOW);
  delay(90);
  digitalWrite(PinLED6, LOW);
  delay(90);

  var ++;
}


void goLuces() {
   digitalWrite(PinLED1, HIGH); // adelante derecha
   digitalWrite(PinLED2, HIGH); 
   digitalWrite(PinLED3, HIGH); //  atras
   digitalWrite(PinLED4, HIGH); // sirena
   digitalWrite(PinLED5, HIGH); // naranja
   digitalWrite(PinLED6, HIGH);  //adelante izq
}


void goLucesAdelante() {
  digitalWrite(PinLED1, HIGH);  // adelante derecha
  digitalWrite(PinLED2, HIGH); // adelante izquierda
}

void goLucesReversa() {
  digitalWrite(PinLED4, HIGH);  // adelante derecha
  digitalWrite(PinLED6, HIGH); // adelante izquierda
}

void goLucesIzquierda() {
  digitalWrite(PinLED2, HIGH);  // adelante derecha
}

void goLucesDerecha() {
  digitalWrite(PinLED1, HIGH);  // adelante derecha
}

void goLucesOff() {
   digitalWrite(LAZER, LOW);
  digitalWrite(PinLED1, LOW);
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED3, LOW);
  digitalWrite(PinLED4, LOW);
  digitalWrite(PinLED5, LOW);
  digitalWrite(PinLED6, LOW);
}

void goLucesColor() {
  digitalWrite(PinLED2, HIGH);
  digitalWrite(PinLED4, HIGH);
}

void goLucesColorSirena() {
  digitalWrite(PinLED3, HIGH);
}

void goLucesOffColor() {
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED4, LOW);
}

void danceDance() {

  led_blink();
  Right();
  delay(70);

  led_blink();
  Left();
  delay(70);

  led_blink();
  Stop();
}
