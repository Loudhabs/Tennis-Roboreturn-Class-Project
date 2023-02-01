/*
both doors are closed
if switch is on
  all 4 motors work, while sensor is sensing
  when distance is at x feet
    stop 4 motors
    open first door, wait 3 seconds, close it
    open second door, wait 3 seconds, open first door
    wait 3 seconds, close both doors
    end of run

run 1:
  when distance is at 6 feet

run 2:
  when distance is at 2 feet

run 3:
  when distance is at 6 feet (with steep ramp)

run 4:
  when distance is at 2 feet (with steep ramp)
 
*/

#include <Servo.h>  // servo library

/*-------------------------VARIABLES FOR SEROVS--------------------*/
Servo servo1;  // servo control object
Servo servo2;
Servo servo3;

const int servo1Pin = 9; //9; //gotta be PMW or analog
const int servo2Pin = 10; //10; //gotta be PMW
const int servo3Pin = 11;

/*
 * //keep range between 20 and 160
servo1:
   closed: 160
   open: 0
servo2:
   closed: 135
   open: 0
servo3:
   closed: 170
   open: 0
 */

/*-------------------------VARIABLES FOR PING SENSOR--------------------*/
//const int trigPin = 7; //11;           //connects to the trigger pin on the distance sensor
//const int echoPin = 8; //12;           //connects to the echo pin on the distance sensor

const int trigPin = A5; //11;
const int echoPin = A4; //12; 

const int RedLedPin = 2; //red LED
const int YellowLedPin = 3; //yellow LED
const int GreenLedPin = 4; //green LED
const int BlueLedPin = 7; //blue LED

float distance = 0;               //stores the distance measured by the distance sensor
int repetition = 0;


/*-------------------------VARIABLES FOR MOTORS--------------------*/
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 6;//A1; //7;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 5;//A2; //8;            //control pin 2 on the motor driver for the right motor
const int PWMA = 3;//A3; //6;            //speed control pin on the motor driver for the right motor

int motorSpeed = 255;       //starting speed for the motor;  0-255 (+ or -)


const int switch1Pin = 2;
const int switch2Pin = 4;
const int switch3Pin = 7;
const int switch4Pin = 12;

bool firstSwitch;
bool secondSwitch;
bool thirdSwitch;
bool fourthSwitch;

/*-----------------------------------------------------------*/
/*-------------------------SETUP FUNCTION--------------------*/
/*-----------------------------------------------------------*/

void setup()
{
  /*-------------------------SETUP FOR SEROVS--------------------*/
  servo1.attach(servo1Pin, 900, 2100);  //Connect the servo to pin 9
								//with a minimum pulse width of
								//900 and a maximum pulse width of
								//2100. 
//                
  servo2.attach(servo2Pin, 900, 2100);  //Connect the servo to pin 9
//                //with a minimum pulse width of
//                //900 and a maximum pulse width of
//                //2100. 

  servo3.attach(servo3Pin, 900, 2100);

  /*-------------------------SETUP FOR PING SENSOR--------------------*/
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

////  /*-------------------------SETUP FOR MOTORS--------------------*/
////  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

////  /*-------------------------SETUP FOR SWITCHES--------------------*/
  pinMode(switch1Pin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped
  pinMode(switch2Pin, INPUT_PULLUP);
  pinMode(switch3Pin, INPUT_PULLUP);
  pinMode(switch4Pin, INPUT_PULLUP);

////  /*-------------------------OVERALL SETUP--------------------*/

  //CLOSE ALL SERVOS
  servo1.write(160);
  servo2.write(135);
  servo3.write(170);

}

/*-----------------------------------------------------------*/
/*-------------------------LOOP FUNCTION--------------------*/
/*-----------------------------------------------------------*/

void loop()
{  
  distance = getDistance();
  runProgram(distance);
}

/*-----------------------------------------------------------*/
/*-------------------------OTHER FUNCTIONS--------------------*/
/*-----------------------------------------------------------*/

void runProgram(int distance)
{
  firstSwitch = digitalRead(switch1Pin) == HIGH;
  secondSwitch = digitalRead(switch2Pin) == HIGH;
  thirdSwitch = digitalRead(switch3Pin) == HIGH;
  fourthSwitch = digitalRead(switch4Pin) == HIGH;
  bool arrayOfSwitches[] = {firstSwitch, secondSwitch, thirdSwitch, fourthSwitch};

 int count = 0;
  for (int i=0; i<sizeof(arrayOfSwitches); i++)
  {
    if (arrayOfSwitches[i])
      count++;   
  }

  if ((count > 1) || (count == 0))
  {
    spinMotor(0);
//    motorSpeed = 255;
  }
  
  else if (firstSwitch)         //if the switch is on...
    firstRun(distance);
    
  else if (secondSwitch)  
    secondRun(distance);
    
  else if (thirdSwitch)  
    thirdRun(distance);  
    
  else if (fourthSwitch) 
    fourthRun(distance); 
}


void firstRun(int distance)
{
  if (distance < 5)
      spinMotor(motorSpeed); 
  else
  {
//    spinMotor(motorSpeed);
//    delay(50);
    spinMotor(0);
    delay(500);
    
    servo1.write(0);
    delay(2000);
    servo1.write(160);
    delay(500);
    servo2.write(0);
    delay(2000);
    servo1.write(0);
    delay(2000);
    
    servo1.write(160);
    servo2.write(135);
  }
}

void secondRun(int distance)
{
  if (distance < 5)
      spinMotor(motorSpeed);
  else
  {
    if (repetition == 0)
    {
      spinMotor(motorSpeed);
      delay(700);
      repetition++;
    }
    else
    {
      spinMotor(0);
      delay(500);
      
      servo1.write(0);
      delay(2000);
      servo1.write(160);
      delay(500);
      servo2.write(0);
      delay(2000);
      servo1.write(0);
      delay(2000);
      
      servo1.write(160);
      servo2.write(135);
    }
  } 
}

void thirdRun(int distance)
{
  if (distance < 5)
      spinMotor(motorSpeed); 
  else
  {
//    spinMotor(motorSpeed);
//    delay(500);
    spinMotor(0);
    delay(500);
    
    servo1.write(0);
    delay(250);
    servo2.write(0);
    delay(3000);
    servo2.write(135);
    delay(500);
    servo3.write(0);
    delay(2000);
    servo2.write(0);
    delay(3500);
    
    servo1.write(160);
    servo2.write(135);
    servo3.write(170);
  }
}

void fourthRun(int distance)
{ 
  if (distance < 5)
    spinMotor(motorSpeed);
  else
  {
    if (repetition == 0)
    {
      spinMotor(motorSpeed);
      delay(700);
      repetition++;
    }
    else
    {
      spinMotor(0);
      delay(500);
      
      servo1.write(0);
      delay(250);
      servo2.write(0);
      delay(3000);
      servo2.write(135);
      delay(500);
      servo3.write(0);
      delay(2000);
      servo2.write(0);
      delay(3500);
      
      servo1.write(160);
      servo2.write(135);
      servo3.write(170);
    }
  } 
}


//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);

//  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  analogWrite(trigPin, 255);
  delayMicroseconds(2);
  analogWrite(trigPin, 0);

  echoTime = pulseIn(echoPin, 255);

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

//For motor
void spinMotor(int theSpeed)                       //function for driving the right motor
{
  if (theSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low

//    analogWrite(AIN1, 255);
//    analogWrite(AIN2, 0);
  }
  else if (theSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high

//    analogWrite(AIN1, 0);
//    analogWrite(AIN2, 255);
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low

//    analogWrite(AIN1, 0);
//    analogWrite(AIN2, 0);
  }
  
  analogWrite(PWMA, abs(theSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
