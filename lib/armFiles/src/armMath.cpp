#include "arm.h"
#include "Arduino.h"

float delta = 1;

#define MAX_ROT 180

Polar armMembers[NUM_ARM_MEMBERS] = { {10, 0}};

Rect target {0, 0};

float maxArmLen;

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

void printDebug(float baseArmAngle, float forearmAngle, float targetAngle) {

  Serial.print(baseArmAngle);
  Serial.print(", ");
  Serial.print(forearmAngle);
  Serial.print(", ");
  Serial.println(targetAngle);
  
}

int computeServoAngle(int servoIdx, SERVO_DIR servoDir) { // TODO - clean up this method
  if(servoIdx >= 0 && servoIdx < NUM_ARM_MEMBERS) {  
    
    bool aboveMinRot = armMembers[servoIdx].angle > 2*delta;
    bool belowMaxRot = armMembers[servoIdx].angle < (MAX_ROT - 2*delta);

    if(servoDir == CW && aboveMinRot) {
      armMembers[servoIdx].angle -= delta;
    }
    else if(servoDir == CCW && belowMaxRot) {
      armMembers[servoIdx].angle += delta;
    }
  }

  return floor(armMembers[servoIdx].angle);
}
