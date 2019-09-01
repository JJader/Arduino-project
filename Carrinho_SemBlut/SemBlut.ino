#include<SoftwareSerial.h>
//  tx --> pode ir no arduino //2
//  rx --> precisa passar pelo conversor //3
int IN1 = 7;
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;
#define led 8
#define buz 9


int veloA = 11, veloB = 10;
float fat = 0;
char comando;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(veloB, OUTPUT);
  pinMode(veloA, OUTPUT);
  delay(3000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  parado();
}

void loop() {
  while (Serial.available()) {
    comando = Serial.read();
    Serial.println(comando);
    analogWrite(veloA, fat);
    analogWrite(veloB, fat);

    switch (comando) {

      case '0':
        fat = 0;
        break;

      case '1':
        fat = 25.5 * 1;
        break;

      case '2':
        fat = 25.5 * 2;
        break;

      case '3':
        fat = 25.5 * 3;
        break;

      case '4':
        fat = 25.5 * 4;
        break;

      case '5':
        fat = 25.5 * 5;
        break;

      case '6':
        fat = 25.5 * 6;
        break;

      case '7':
        fat = 25.5 * 7;
        break;

      case '8':
        fat = 25.5 * 8;
        break;

      case '9':
        fat = 25.5 * 9;
        break;

      case 'a':
        fat = 25.5 * 10;
        break;

      case 'A':
        fat = 25.5 * 10;
        break;

      default:

        if (comando == 'w') {
          funcLed(!digitalRead(led));
        }
        else if (comando == 'V' || comando == 'v') {
          funcBuz();
        }
        else if (comando == 'F' || comando == 'f') {
          frente();
        }
        else if (comando == 'B' || comando == 'b') {
          tras();
        }
        else if (comando == 'L' || comando == 'l') {
          esquerda();
        }
        else if (comando == 'R' || comando == 'r') {
          direita();
        }
        else if (comando == 'P' || comando == 'p'){
          parado();
        }
        break;
    }

  }
}


void funcLed(bool a) {
  digitalWrite(led, a);
  Serial.println("Okay");
}

void funcBuz() {
  digitalWrite(buz, HIGH);
  delay(500);
  digitalWrite(buz, LOW);
  delay(10);
  Serial.println("Okay");
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Okay");
  //Gira o Motor A e B no sentido horario
}

void tras() {
  //Gira o Motor A e B no sentido anti-horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Okay");
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Okay");
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Okay");
}

void parado() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  Serial.println("Okay");
}
