#include "Servo.h"
#include "Arduino.h"

typedef struct {
  float x, y;
} Rect;

typedef struct {
  float len, angle;
} Polar;

void initArm();

void runArm();
