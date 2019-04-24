#include <stepperLib.h>

Stepper motors;
int targetL = -500;
int targetR = -500;

void setup()
{  
  motors.setStepTarget( targetL, targetR);
}

void loop()
{
  for(int i = 0; i<10; i++)
  {
    motors.moveToTarget(0);
    delay(500);
    targetL = -targetL;
    targetR = -targetR;
    motors.setStepTarget( targetL, targetR);
  }
  motors.moveToTarget(1);
  while(1);
}
