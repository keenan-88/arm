#include "Arduino.h"
#include "Servo.h"
#include <arm.h>



void setup()
{
  Serial.begin(9600);
  initArm();
}


void loop()
{
  runArm();
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