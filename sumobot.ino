#include <Servo.h> 

Servo servoL;
Servo servoR;

/* pins */
#define LED 13
#define SERVO_LEFT 9
#define SERVO_RIGHT 10
#define LINE_LEFT_SENSOR 3
#define LINE_MIDDLE_SENSOR 2
#define LINE_RIGHT_SENSOR 1

/* servo settings */
#define SERVO_CENTER 90
#define SERVO_SPEED 10
#define SERVO_LEFT_FORWARD  (SERVO_CENTER + SERVO_SPEED)
#define SERVO_RIGHT_FORWARD (SERVO_CENTER - SERVO_SPEED)
#define SERVO_LEFT_REVERSE  (SERVO_CENTER - SERVO_SPEED)
#define SERVO_RIGHT_REVERSE (SERVO_CENTER + SERVO_SPEED)

/* sensors */
#define READ_LINE(analog, distance) (analogRead(analog) < distance)
/* field */
#define LINE_LEFT READ_LINE(LINE_LEFT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_RIGHT READ_LINE(LINE_RIGHT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_MIDDLE READ_LINE(LINE_MIDDLE_SENSOR, LIGHT_INTENSITY_MIDDLE)
/* calibration*/
#define LIGHT_INTENSITY 700
#define LIGHT_INTENSITY_LEFT LIGHT_INTENSITY
#define LIGHT_INTENSITY_RIGHT LIGHT_INTENSITY
#define LIGHT_INTENSITY_MIDDLE LIGHT_INTENSITY

void setup() 
{ 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  servoL.attach(SERVO_LEFT);
  servoR.attach(SERVO_RIGHT);
  halt();
  //delay(500);
  digitalWrite(LED, LOW);
} 

void loop()
{
  if (!LINE_RIGHT){
    reverse(800);
    left(500);
  }else if (!LINE_LEFT){
    reverse(800);
    right(500);
  }else{
    forward(100);
  }
  //halt(500);
} 





void forward(int time)
{
  servoL.write(SERVO_LEFT_FORWARD);
  servoR.write(SERVO_RIGHT_FORWARD);
  delay(time);
}

void reverse(int time)
{
  servoL.write(SERVO_LEFT_REVERSE);
  servoR.write(SERVO_RIGHT_REVERSE);
  delay(time);
}

void halt() { halt(0); }
void halt(int time)
{
  servoL.write(SERVO_CENTER);
  servoR.write(SERVO_CENTER);
  delay(time);
}

void left(int time)
{
  servoL.write(SERVO_LEFT_REVERSE);
  servoR.write(SERVO_RIGHT_FORWARD);
  delay(time);
}

void right(int time)
{
  servoL.write(SERVO_LEFT_FORWARD);
  servoR.write(SERVO_RIGHT_REVERSE);
  delay(time);
}


