#include <stepperLib.h>

Stepper motors;
int targetL = -100;
int targetR = -100;

void setup()
{  
    motors.setStepTarget( targetL, targetR);
}

void loop()
{
  motors.moveToTarget();
  targetL = -targetL;
  targetR = -targetR;
  motors.setStepTarget( targetL, targetR);
}
