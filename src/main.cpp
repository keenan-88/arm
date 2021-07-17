#include "Arduino.h"
#include <arm.h>

void setup()
{
  Serial.begin(9600);
  initServos();
}

SERVO_DIR servoInputDir;
int servoAngle;

void indent(int numSpaces){
  for(int spacesPrinted = 0; spacesPrinted < numSpaces; spacesPrinted++) {
    Serial.print("    ");
  }
}

void loop()
{
  for(int servoIdx = 0; servoIdx < NUM_ARM_MEMBERS; servoIdx++) {
    servoInputDir = getServoInputDir(servoIdx);

    servoAngle = computeServoAngle(servoIdx, servoInputDir);
    //indent(servoIdx);
    //Serial.println(servoAngle);

    writeServoAngle(servoIdx, servoAngle);

    delay(5);
  }
}