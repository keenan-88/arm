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

    //float angleInRadians = 1.0 * servoAngle/180.0*PI;

    //sprintf(debugBuf, "dir: %d, angle: %d, ", servoInputDir, servoAngle);
    //Serial.print(debugBuf);
    //Serial.println(angleInRadians);

    writeServoAngle(servoIdx, servoAngle);
  }
}