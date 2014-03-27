#include <Servo.h> 

Servo servoL;
Servo servoR;

int searchVector;

/* pins */
#define LED 13
#define SERVO_LEFT 9
#define SERVO_RIGHT 10
#define FRONT_RIGHT_SENSOR 5
#define FRONT_LEFT_SENSOR 4
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

/* calibration*/
#define ENEMY_DISTANCE 200
#define LIGHT_INTENSITY 700
#define SEARCH_MAX 3000
#define SEARCH_INCREMENT 100
#define ENEMY_DISTANCE_LEFT ENEMY_DISTANCE
#define ENEMY_DISTANCE_RIGHT ENEMY_DISTANCE
#define LIGHT_INTENSITY_LEFT LIGHT_INTENSITY
#define LIGHT_INTENSITY_RIGHT LIGHT_INTENSITY
#define LIGHT_INTENSITY_MIDDLE LIGHT_INTENSITY

/* sensors */
#define READ_LINE(analog, distance) (analogRead(analog) > distance)
#define READ_ENEMY(analog, distance) (analogRead(analog) > distance)
/* field */
#define LINE_LEFT READ_LINE(LINE_LEFT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_RIGHT READ_LINE(LINE_RIGHT_SENSOR, LIGHT_INTENSITY_RIGHT)
#define LINE_MIDDLE READ_LINE(LINE_MIDDLE_SENSOR, LIGHT_INTENSITY_MIDDLE)
#define LINE_ANY (LINE_LEFT || LINE_MIDDLE || LINE_RIGHT)
/* enemy */
#define ENEMY_LEFT READ_ENEMY(FRONT_LEFT_SENSOR, ENEMY_DISTANCE_LEFT)
#define ENEMY_RIGHT READ_ENEMY(FRONT_RIGHT_SENSOR, ENEMY_DISTANCE_RIGHT)
#define ENEMY_FRONT (ENEMY_LEFT && ENEMY_RIGHT)
/* search */
#define SEARCH_LEFT (searchVector < (SEARCH_MAX / 2))
#define SEARCH_RIGHT (searchVector > (SEARCH_MAX / 2))


void setup() 
{ 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  servoL.attach(SERVO_LEFT);
  servoR.attach(SERVO_RIGHT);
  halt();
  searchVector = 0;
  delay(500); //for debug resets
  digitalWrite(LED, LOW);
} 

void loop()
{
  /* avoid the edges */
  if (LINE_MIDDLE) {
    reverse(800);
  } else if (LINE_RIGHT) {
    reverse(200);
    left(500);
  } else if (LINE_LEFT) {
    reverse(200);
    right(500);
  }else {
    /* drive towards enemy */
    if (ENEMY_LEFT && !ENEMY_RIGHT) {
      left(200);
    }
    if (ENEMY_RIGHT & !ENEMY_LEFT) {
      right(200);
    }
    if (ENEMY_LEFT && ENEMY_RIGHT) {
      forward(200);
    }
    //search for enemy
    if (!ENEMY_LEFT && !ENEMY_RIGHT) {
      if (SEARCH_LEFT) {
        left(SEARCH_INCREMENT);
      }
      if (SEARCH_RIGHT) {
        right(100);
      }
      searchVector = (searchVector + SEARCH_INCREMENT) % SEARCH_MAX;
    }
  }
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


