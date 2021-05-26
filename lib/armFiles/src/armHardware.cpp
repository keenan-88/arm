#include "arm.h"
#include "Arduino.h"

typedef struct {
    int btnCWID, btnCCWID;
    int ctrlPin;
    Servo servo;
} ServoControl;

ServoControl servoControl[NUM_ARM_MEMBERS] = { {2, 3, 8, Servo()} };

Servo shoulder;
Servo elbow;

void initServos() {

    for(int servoIdx = 0; servoIdx < NUM_ARM_MEMBERS; servoIdx++) {
        pinMode(servoControl[servoIdx].btnCCWID, INPUT);
        pinMode(servoControl[servoIdx].btnCWID, INPUT);
        servoControl[servoIdx].servo.attach(servoControl[servoIdx].ctrlPin);
        servoControl[servoIdx].servo.write(0);
    }
}

SERVO_DIR getServoInputDir(int servoIdx) {
    SERVO_DIR servoDir = NO_DIR;

    if(servoIdx >= 0 && servoIdx < NUM_ARM_MEMBERS) {
        bool CCWInput = digitalRead(servoControl[servoIdx].btnCCWID);
        bool CWInput  = digitalRead(servoControl[servoIdx].btnCWID);

        if(CCWInput && CWInput) {
            servoDir = NO_DIR;
        }
        else if(CCWInput) {
            servoDir = CCW;
        }
        else if(CWInput) {
            servoDir = CW;
        }
    }

    return servoDir;
}

void writeServoAngle(int servoIdx, int angle) {
    if(servoIdx >= 0 && servoIdx < NUM_ARM_MEMBERS) {
        servoControl[servoIdx].servo.write(angle);
    }
}
