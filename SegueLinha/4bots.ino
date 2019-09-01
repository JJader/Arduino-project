/*
** Line Follower Basic v. 0.5
** Last Update: 2013-05-21
*/

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
#define maxSpeed 65

/* variables to keep track of current speed of motors */
int motorLSpeed = 0;
int motorRSpeed = 0;

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
  
  /* Change the PWM frequency of digital pins 5 and 6 (timer0) to Phase-correct PWM of 31.250 kHz
  from the default of ~500Hz. Using code from Adjusting PWM Frequencies
  http://playground.arduino.cc/Main/TimerPWMCheatsheet
  
  This requires a separate change in the wiring.c function in the Arduino program files 
  hardware\arduino\cores\arduino\wiring.c from:
  #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
  
  to:
  #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(1 * 510))
  
  Without the change to wiring.c time functions (millis, delay, as well as libraries using them
  will not work corectly.
  */
  //TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); 
  //TCCR0B = _BV(CS00); 
}

void loop() {
 Scan();
 UpdateError();
 UpdateCorrection();
 Drive();
}

void Scan() {
  // Initialize counters, sums etc.

  count = 0;

  irSensors = B00000000;
    
  for (int i = 0; i < 8; i++) {
    
    if (digitalRead(irPins[i])==0){
      irSensorDigital[i] = 0;
    } else {
      irSensorDigital[i] = 1;
    }
         
    Serial.print(irSensorDigital[i]);
    Serial.print("|");
    count = count + irSensorDigital[i];
    int b = 7-i;
    irSensors = irSensors + (irSensorDigital[i]<<b);
  }
  
  Serial.print(" - ");
      
}

void UpdateError() {
  
  errorLast = error;  
  
  switch (irSensors) {
     
    case B00000000:
       if (errorLast < 0) { error = -180;}
       else if (errorLast > 0) {error = 180;}
       break;
     
     case B00000001: // leftmost sensor on the line
       error = -150;
       break;
      
     case B00000010:
       error = -90;
       break;

     case B00000100: 
       error = -30;
       break;
       
     case B00001000: 
       //error = -10;
       error = 0;
       break;

     case B00010000:  
       //error = 10;
       error = 0;
       break;

     case B00100000:  
       error = 30;
       break;
       
     case B01000000: 
       error = 90;
       break;           

     case B10000000: // rightmost sensor on the line
       error = 150;
       break;
       
/* 2 Sensors on the line */         
     
     case B11000000: // rightmost sensor on the line
       error = 150;
       break;
       
     case B00000110:
       error = -120;
       break;
      
     case B00001100:
       error = -60;
       break;

     case B00011000: 
       error = 0;
       break;

     case B00110000: 
       error = 60;
       break;           

     case B01100000:
       error = 120;
       break;
     
     case B00000011: // leftmost sensor on the line
       error = -150;
       break;
       

/* 3 Sensors on the line */    
     
     case B11100000: // rightmost sensor on the line
       error = 150;
       break;
         
     case B01110000:
     case B00111000:
       //error = 150;
       error = 50;
       break;
      
     case B00001110:
     case B00011100:
       //error = -150;
       error = -50;
       break;
       
     case B00000111: // leftmost sensor on the line
       error = -150;
       break;

 /* 4 Sensors on the line */       
     case B01111000:
       //error = 150;
       error = 75;
       break;

     case B01110100:
       //error = 150;
       error = 75;
       break;

      case B00111100:
       error = 0;
       break;
     
     case B00011110:
       //error = -150;
       error = -75;
       break;
       
     case B00101110:
       //error = -150;
       error = -70;
       break;
       
     case B00011101:
       error = -150;
       break;

      case B01011100:
       error = 150;
       break;

/* 5 Sensors on the line */      
     
     case B11111000:
       error = 150;
       break;
      
      case B01111100:
       error = 150;
       break;
     
     case B00111110:
       error = -150;
       break;
       
     case B00011111:
       error = -150;
       break;
      
     case B01111110:
       lap = lap + 1; // increment laps when start/finish line is crossed
       error = 0;
       break;

/* 6 Sensors on the line */      
     
     case B11111100:
       error = 150;
       break;
      
     case B00111111:
       error = -150;
       break;
      
     case B11111111:
       //if (errorLast < 0) { error = -180;}
       //else if (errorLast > 0) {error = 180;}
       //finish = 1;
       error = errorLast;
       break;
   
     default:
     error = errorLast;
  }
}

void UpdateCorrection() {

  if (error >= 0 && error < 30) {
    correction = 0;
  }
  
  else if (error >=30 && error < 60) {
    correction = 15;
  }
  
  else if (error >=60 && error < 90) {
    correction = 40;
  }
  
  else if (error >=90 && error < 120) {
    correction = 55;
  }  
  
  else if (error >=120 && error < 150) {
    correction = 75;
  } 
  
  else if (error >=150 && error < 180) {
    correction = 255;
  }   

  else if (error >=180) {
    correction = 305;
  }

  if (error <= 0 && error > -30) {
    correction = 0;
  }
  
  else if (error <= -30 && error > -60) {
    correction = -15;
  }
  
  else if (error <= -60 && error > -90) {
    correction = -40;
  }
  
  else if (error <= -90 && error > -120) {
    correction = -55;
  }  
  
  else if (error <= -120 && error > -150) {
    correction = -75;
  } 
  
  else if (error <= -150 && error > -180) {
    correction = -255;
  }   

  else if (error <= -180) {
    correction = -305;
  }
  
  if (correction >= 0) {
    motorRSpeed = maxSpeed - correction;
    motorLSpeed = maxSpeed;
  }
  
  else if (correction < 0) {
    motorRSpeed = maxSpeed;
    motorLSpeed = maxSpeed + correction;
  }
}

void Drive() {

  if (motorRSpeed > maxSpeed) {motorRSpeed = maxSpeed;}
  else if (motorRSpeed < -1*maxSpeed) {motorRSpeed = -1*maxSpeed;}
  
  if (motorLSpeed > maxSpeed) {motorLSpeed = maxSpeed;}
  else if (motorLSpeed < -1*maxSpeed) {motorLSpeed = -1*maxSpeed;}

  if (finish == 1){
    motorRSpeed = 0;
    motorLSpeed = 0;
  }
  
  if (motorRSpeed > 0) { // right motor forward (using PWM)
     
     Serial.print("RF: ");
     Serial.print(motorRSpeed);
     
     analogWrite(motorREnable, motorRSpeed);
     analogWrite(motorRPin1, 255);
     analogWrite(motorRPin2, 0);
  } 
  
  else if (motorRSpeed < 0) {// right motor reverse (using PWM)
     
     Serial.print("RB: ");
     Serial.print(motorRSpeed);
     
     analogWrite(motorREnable, abs(motorRSpeed));
     analogWrite(motorRPin1, 0);
     analogWrite(motorRPin2, 255);
  } 
  
  else if (motorRSpeed == 0) { // right motor fast stop
     
     Serial.print("RFS");
     
     analogWrite(motorREnable, 255);
     analogWrite(motorRPin1, 0);
     analogWrite(motorRPin2, 0);
  }
  
  if (motorLSpeed > 0) { // left motor forward (using PWM)
     
     Serial.print("| LF: ");
     Serial.println(motorLSpeed);
     
     analogWrite(motorLEnable, motorLSpeed);
     analogWrite(motorLPin1, 255);
     analogWrite(motorLPin2, 0);
  } 
  
  else if (motorLSpeed < 0) { // left motor reverse (using PWM)
    
     Serial.print("| LB: ");
     Serial.println(motorLSpeed);
     
     analogWrite(motorLEnable, abs(motorLSpeed));
     analogWrite(motorLPin1, 0);
     analogWrite(motorLPin2, 255);
  } 
  
    else if (motorLSpeed == 0) { // left motor fast stop
      
     Serial.println("| LFS");
     
     analogWrite(motorLEnable, 255);
     analogWrite(motorLPin1, 0);
     analogWrite(motorLPin2, 0);
  }
}
