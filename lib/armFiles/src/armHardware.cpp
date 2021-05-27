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

        Serial.println(servoControl[servoIdx].btnCCWID);
        Serial.println(servoControl[servoIdx].btnCWID);
    }
}

SERVO_DIR getServoInputDir(int servoIdx) {
    SERVO_DIR servoDir = NO_DIR;

    if(servoIdx >= 0 && servoIdx < NUM_ARM_MEMBERS) {
        bool CCWInput = digitalRead(servoControl[servoIdx].btnCCWID);
        bool CWInput  = digitalRead(servoControl[servoIdx].btnCWID);

        /*Serial.print(CCWInput);
        Serial.print(", ");
        Serial.println(CWInput);
        */
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
int pulseWidth = 0;
void writeServoAngle(int servoIdx, float angle) {

    if(servoIdx >= 0 && servoIdx < NUM_ARM_MEMBERS) {                
        servoControl[servoIdx].servo.write(angle);
    }
}
