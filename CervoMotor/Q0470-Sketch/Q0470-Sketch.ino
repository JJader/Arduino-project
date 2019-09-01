/*
     Q0470
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  PWM I2C
     DATA:    04/06/2019
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



// INSTANCIANDO OBJETOS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// DECLARAÇÃO DE FUNÇÕES
void writeServos(int posicao, int tempo);
void beginServos();
char comando;
void setup() {
  Serial.begin(9600);
  beginServos(); // INCIA OS SERVOS
  delay(300);
}

void loop() {
 while(Serial.available()){
comando = Serial.read();
  switch(comando){

    case 'z':
    writeServos(2, 100);
    delay(500);
    writeServos(1, 80);
    delay(500);
    writeServos(1, 10);
    writeServos(2, 10);
    delay(1000);
   /* 
    writeServos(11, 0);
    delay(500);
    writeServos(11, 60);
    delay(1000);
    writeServos(11, 0);
    delay(500);
     */ 
    break;
    case '1':
    writeServos(1, 100);
    delay(500);
    writeServos(1, 0);
    delay(500);
    break;
    
    case '2':
    writeServos(2, 150);
    delay(2000);
    writeServos(2, 0);
    delay(2000);
    break;

    case '3':
    writeServos(3, 90);
    delay(500);
    writeServos(3, 0);
    delay(500);
    break;
    
    case '4':
    writeServos(4, 90);
    delay(500);
    writeServos(4, 0);
    delay(500);
    break;

    case '5':
    writeServos(5, 100);
    delay(500);
    writeServos(5, 0);
    delay(500);
    break;
    
    case '6':
    writeServos(6, 90);
    delay(500);
    writeServos(6, 0);
    delay(500);
    break;

    case '7':
    writeServos(7, 90);
    delay(500);
    writeServos(7, 0);
    delay(500);
    break;
    
    case '8':
    writeServos(8, 90);
    delay(500);
    writeServos(8, 0);
    delay(500);
    break;

    case '9':
    writeServos(9, 90);
    delay(500);
    writeServos(9, 0);
    delay(500);
    break;

    case 'a':
    writeServos(10, 0);
    delay(500);
    writeServos(10, 90);
    delay(500);
    break;
    
    case 'b':
    writeServos(11, 45);
    delay(500);
    writeServos(11, 90);
    delay(500);
    break;

    
    case 'c':
    writeServos(12, 90);
    delay(500);
    writeServos(12, 0);
    delay(500);
    break;

    
    case 'd':
    writeServos(13, 90);
    delay(500);
    writeServos(13, 0);
    delay(500);
    break;
  }
 }
}
// IMPLEMENTO DE FUNÇÕES
void writeServos(int nServo, int posicao) {
#define SERVOMIN  173  // VALOR PARA UM PULSO MAIOR QUE 1 mS
#define SERVOMAX  540 // VALOR PARA UM PULSO MENOR QUE 2 mS

  int pos = map ( posicao , 0 , 180 , SERVOMIN, SERVOMAX);
  pwm.setPWM(nServo , 0, pos);
}

void beginServos() {

#define Frequencia 100 // VALOR DA FREQUENCIA DO SERVO 

  pwm.begin(); // INICIA O OBJETO PWM
  pwm.setPWMFreq(Frequencia); // DEFINE A FREQUENCIA DE TRABALHO DO SERVO
}
