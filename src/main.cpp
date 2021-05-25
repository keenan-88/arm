#include "Arduino.h"
#include "Servo.h"

typedef struct {
  float x, y;
} Rect;

typedef struct {
  float len, angle;
} Polar;

Polar toPolar(Rect rect) {
  Polar polar;

  polar.len = sqrt(pow(rect.x, 2) + pow(rect.y, 2));
  polar.angle = PI/2 - atan(rect.x/rect.y);

  return polar;
}

Rect toRect(Polar polar) {
  Rect rect;

  rect.x = cos(polar.angle) * polar.len;
  rect.y = sin(polar.angle) * polar.len;

  return rect;
}

float toDeg(float radians) {
  return radians/PI*180;
}

float cosineLaw(float adj1len, float adj2len, float oppLen) {
  float numerator = - pow(oppLen, 2) + pow(adj1len, 2) + pow(adj2len, 2);
  float denominator = 2 * adj1len * adj2len;

  float angle;

  if(denominator == 0) {
    angle = PI/2;
  }
  else {
    angle = acos(numerator / denominator);
  }
 

  return angle;
}

Polar baseArm {14, 0};
Polar foreArm {13, 0};

Servo shoulder;
Servo elbow;

Rect target {baseArm.len + foreArm.len, 0};

float maxArmLen = baseArm.len + foreArm.len;

int upPin = 4;
int downPin = 3;
int leftPin = 5;
int rightPin = 2;

void setup()
{
  Serial.begin(9600);
  shoulder.attach(9);
  elbow.attach(10);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  shoulder.write(0);
  elbow.write(0);
}

void printDebug(float baseArmAngle, float forearmAngle, float targetAngle) {
  Serial.print(baseArmAngle);
  Serial.print(", ");
  Serial.print(forearmAngle);
  Serial.print(", ");
  Serial.println(targetAngle);
}

float delta = 1;

void loop()
{

  if(digitalRead(leftPin) && (baseArm.angle + 2*delta) < 120) {
    baseArm.angle += delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    shoulder.write(baseArm.angle);
    delay(25);
  } 
  else if(digitalRead(rightPin) && (baseArm.angle - 2*delta) > 0) {
    baseArm.angle -= delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    shoulder.write(baseArm.angle);
    delay(25);
  }
  
  if(digitalRead(upPin) && (foreArm.angle + 2*delta) < 120) {
    foreArm.angle += delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    elbow.write(foreArm.angle);
    delay(25);
  } 
  else if(digitalRead(downPin) && (foreArm.angle - 2*delta) > 0) {
    foreArm.angle -= delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    elbow.write(foreArm.angle);
    delay(25);
  }
}

/*


if(digitalRead(leftPin) && (baseArm.angle + 2*delta) < 180) {
    baseArm.angle += delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    shoulder.write(baseArm.angle);
    delay(25);
  } 
  else if(digitalRead(rightPin) && (baseArm.angle - 2*delta) > 0) {
    baseArm.angle -= delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    shoulder.write(baseArm.angle);
    delay(25);
  }
  
  if(digitalRead(upPin) && (foreArm.angle + 2*delta) < 180) {
    foreArm.angle += delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    elbow.write(foreArm.angle);
    delay(25);
  } 
  else if(digitalRead(downPin) && (foreArm.angle - 2*delta) > 0) {
    foreArm.angle -= delta;
    printDebug(baseArm.angle, foreArm.angle, 0);
    elbow.write(foreArm.angle);
    delay(25);
  }

  */