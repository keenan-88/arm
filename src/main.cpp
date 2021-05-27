#include "Arduino.h"
#include <arm.h>

void setup()
{
  Serial.begin(9600);
  initServos();
}


void loop()
{
  SERVO_DIR servoInputDir;
  int servoAngle;
  //char debugBuf[100];

  for(int servoIdx = 0; servoIdx < NUM_ARM_MEMBERS; servoIdx++) {
    servoInputDir = getServoInputDir(servoIdx);

    
    servoAngle = computeServoAngle(servoIdx, servoInputDir);

    writeServoAngle(servoIdx, servoAngle);

    delay(5);
  }
}