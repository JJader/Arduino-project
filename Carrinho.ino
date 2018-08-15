#include<SoftwareSerial.h>
SoftwareSerial bluetooth(2,3); //rx tx do arduino
//  tx --> pode ir no arduino //2
//  rx --> precisa passar pelo conversor //3
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
#define led 8
char comando;

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(led, OUTPUT);

  delay(3000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  parado();
}

void loop() {
   while (bluetooth.available()) {
    comando = bluetooth.read();
    Serial.println(comando);

    if (comando == 'W'){
      digitalWrite(led, HIGH);
    }
    if (comando == 'w'){
      digitalWrite(led, LOW);
    }
    if (comando == 'F') {
      frente();
    }
    else if (comando == 'B') {
      tras();
    }
    else if (comando == 'L') {
      esquerda();
    }
    else if (comando == 'R') {
      direita();
    } else {
      parado();
    }
  }
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Gira o Motor A e B no sentido horario
  
}

void tras() {
  //Gira o Motor A e B no sentido anti-horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  
}

void esquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void direita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parado() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
