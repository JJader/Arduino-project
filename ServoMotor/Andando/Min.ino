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

    case 'L':
    writeServos(11, 0);
    writeServos(12, 40);
    delay(100);
    break;

    case 'l':
    writeServos(11, 140);
    writeServos(12, 120);
    delay(100);
    break;
    
    case 'R':
    writeServos(1, 40);
    writeServos(2, 160);
    delay(50);
    writeServos(1, 150);
    delay(100);
    break;
    
    case 'r':
    writeServos(1, 100);
    writeServos(2, 0);
    delay(50);
    writeServos(1, 100);
    delay(100);
    break;
    
    
    case 'A':
    writeServos(1, 90);
    writeServos(2, 90);
    writeServos(11, 90);
    writeServos(12, 90);
    writeServos(7, 90);
    writeServos(3, 60);
    writeServos(14, 110);
    writeServos(15, 90);
    break;

    case '0':
    writeServos(0, 30);
    delay(500);
    writeServos(0, 130);
    delay(500);
    break;
    
    case '1':
    writeServos(1, 30);
    delay(500);
    writeServos(1, 130);
    delay(500);
    break;
    
    case '2':
    writeServos(2, 30);
    delay(500);
    writeServos(2, 130);
    break;

    case '3':
    writeServos(3, 30);
    delay(500);
    writeServos(3, 130);
    delay(500);
    break;
    
    case '4':
   writeServos(4, 0);
    delay(500);
    
    break;

    case '5':
    writeServos(5, 0);
    delay(500);
    
    break;
    
    case '6':
    writeServos(6, 0);
    delay(500);
    break;

    case '7':
    writeServos(7, 180);
    delay(500);
    break;
    
    case '8':
    writeServos(8, 0);
    delay(500);
    break;

    case '9':
    writeServos(9, 0);
    delay(500);
    break;

    case 'a':
    writeServos(10, 0);
    delay(500);
    break;
    
    case 'b':
    writeServos(11, 30);
    delay(500);
    writeServos(11, 130);
    delay(500);
    break;
  
    case 'c':
    writeServos(12, 30);
    delay(500);
    writeServos(12, 130);
    delay(500);
   break;

    case 'd':
    writeServos(13, 0);
    delay(500);
    break;

    
    case 'e':
    writeServos(14, 30);
    delay(500);
    writeServos(14, 130);
    delay(500);
    break;

    
    case 'f':
    writeServos(15, 30);
    delay(500);
    writeServos(15, 130);
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
