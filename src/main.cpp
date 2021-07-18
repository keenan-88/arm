#include <Servo.h>
#include <math.h>
#include "Arduino.h"

#define LKY62_MAX_ROT 180
#define LKY62_MIN_ROT 0

float getAng(float x, float endAng, float P, float K)
{
  float ang = P / (1.0 + exp(K*x)) + endAng;

  return ang;
}

Servo servo;
float servoAng;

void setup() {
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  servo.attach(8);
  servo.write(0);
}

void setServoTo(float* servoAng, float targetAng)
{
  float startAng = *servoAng;
  
  float P = startAng - targetAng;
  float K = pow(fabs(P), -0.65);

  float startX = log(1.0 / (fabs(1-180*P) ) ) / K; 
  float lastX = -startX;
  float x = startX;

  char debug[50];
  sprintf(debug, "startX %d, lastX %d", startX, lastX);
  Serial.println(debug);

  for(; x < lastX; x += 0.03)
  {
    *servoAng = getAng(x, targetAng, P, K);
    servo.write((*servoAng));
    //delay(10);
  }
}

void loop() {

  if(digitalRead(2))
  {
    Serial.println("2");
    servoAng = 0;
    servo.write(servoAng);
  }
  else if(digitalRead(3))
  {
    Serial.println("3");
    setServoTo(&servoAng, 180);
    servo.write(servoAng);
  }
  

  
  
  
}