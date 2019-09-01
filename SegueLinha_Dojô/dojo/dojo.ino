/* Define motor controll inputs */
#define motorRPin1 A5 // signal pin 1 for the right motor, connect to IN1               
#define motorRPin2 A4  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 5; // enable pin for the right motor (needs to be PWM enabled)

#define motorLPin1 A2 // signal pin 1 for the left motor, connect to IN3             
#define motorLPin2 A1 // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 6; // enable pin for the left motor (needs to be PWM enabled)

/* Define the pins for the IR receivers */
const int irPins[8] = {2,3,4,7,8,9,10,11};

// an array to hold boolean values (1/0) for the ir sensors, based on the digital read and the predefined treashold
int irSensorDigital[8] = {0,0,0,0,0,0,0,0}; 

// binary representation of the sensor reading from left to right
int irSensors = B00000000; 

// sensors detecting the line
int count = 0; 

// a score to determine deviation from the line [-180 ; +180]. Negative means the robot is left of the line.
int error = 0;

//  store the last value of error
int errorLast = 0;  

// a coorection value, based on the error that is used to change motor speed with PWM
int correction = 0; 

// keep track of the laps
int lap = 0; 

// to stop the car
int finish = 0;

/* Set up maximum speed and speed for turning (to be used with PWM) */

// PWM to control motor speed [0 - 255]
#define maxSpeed 35

/* variables to keep track of current speed of motors */
int motorLSpeed = 0;
int motorRSpeed = 0;

/* delay de tempo */
long double periodo_loop = 600;  //Período do loop
long double tempo_atual = 0; //Registro do tempo atual

void setup() {
  Serial.begin(9600);

  /* Set up motor controll pins as output */
  pinMode(motorLPin1,OUTPUT);        
  pinMode(motorLPin2,OUTPUT);
  pinMode(motorLEnable,OUTPUT);
  
  pinMode(motorRPin1,OUTPUT);        
  pinMode(motorRPin2,OUTPUT);
  pinMode(motorREnable,OUTPUT);
   
  /* Set-up IR sensor pins as input */
  for (int i = 0; i < 8; i++) {
    pinMode(irPins[i], INPUT);
  }
}


void loop() {
 Scan();

  if (irSensors == 0) { //move forward (using PWM)
    
     Serial.println("Forward");
    
     motorRSpeed = 60;
     motorLSpeed = 60;
     
     analogWrite(motorREnable, motorRSpeed);
     analogWrite(motorLEnable, motorLSpeed);
     
     analogWrite(motorLPin1, 255);
     analogWrite(motorLPin2, 0);
     analogWrite(motorRPin1, 255);
     analogWrite(motorRPin2, 0);
  } 

if (irSensors > 0) { //move forward (using PWM)

       tempo_atual = millis();
    while ((millis() - tempo_atual) < periodo_loop) {
       
       Serial.println("Reverse");
    
       motorRSpeed = 70;
       motorLSpeed = 70;
     
       analogWrite(motorREnable, motorRSpeed);
       analogWrite(motorLEnable, motorLSpeed);
     
       analogWrite(motorLPin1, 0);
       analogWrite(motorLPin2, 255);
       analogWrite(motorRPin1, 0);
       analogWrite(motorRPin2, 255);
     
     }

       tempo_atual = millis();
    while ((millis() - tempo_atual) < periodo_loop) {
       
       Serial.println("Girando");
    
       motorRSpeed = 70;
       motorLSpeed = 70;
     
       analogWrite(motorREnable, motorRSpeed);
       analogWrite(motorLEnable, motorLSpeed);
     
       analogWrite(motorLPin1, 255);
       analogWrite(motorLPin2, 0);
       analogWrite(motorRPin1, 0);
       analogWrite(motorRPin2, 255);
     
     }
     
  } 
 
 
}

void Scan() {
  // Initialize counters, sums etc.

  count = 0;

  irSensors = B00000000;
    
  for (int i = 0; i < 8; i++) {
    
    if (digitalRead(irPins[i])==0){
      irSensorDigital[i] = 1;
    } else {
      irSensorDigital[i] = 0;
    }
         
    Serial.print(irSensorDigital[i]);
    Serial.print("|");
    count = count + irSensorDigital[i];
    int b = 7-i;
    irSensors = irSensors + (irSensorDigital[i]<<b);
  }
  
  Serial.print(" - ");
      
}
