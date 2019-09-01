/*
 * Teste da Ponte H
 * Projeto Seguidor de Linha
 * Locobots
 */

#define IN1 A1  //Roda direita +
#define IN2 A2  //Roda direita -
#define IN3 A4  //Roda esquerda +
#define IN4 A5  //Roda esquerda -
#define ENA1 5  //Enable roda direita
#define ENA2 6  //Enable roda esquerda

long double time_loop = 1;  //Tempo de intervalo do loop em ms
int D = 0;                  //Duty Cicle do PWM
double analog_value;   //Valor convertido de D para a saída digital que varia de 0 a 255

void setup() {

  Serial.begin(9600);
  
  //Definição das portas
  pinMode(IN1 , OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  
}

void loop() {

analog_value = 0;

  //Alimentação do motor da roda direita
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255);

 
  for (analog_value = 0; analog_value < 256; analog_value+=5){
  
    Serial.println(analog_value);
  
    analogWrite(ENA1, 60); //alimentação do sinal em PWM
    analogWrite(ENA2, 60); //alimentação do sinal em PWM

    delay(5000);
 
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);

   

  }


}
