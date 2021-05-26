#include "Servo.h"

#define NUM_ARM_MEMBERS 1

typedef struct {
  float x, y;
} Rect;

typedef struct {
  float len, angle;
} Polar;

typedef enum {
  CW,
  CCW,
  NO_DIR
} SERVO_DIR;

void initServos();

void getArmPos();

SERVO_DIR getServoInputDir(int servoIdx);

int computeServoAngle(int servoIdx, SERVO_DIR servoDir);

void writeServoAngle(int servoIdx, int angle);

