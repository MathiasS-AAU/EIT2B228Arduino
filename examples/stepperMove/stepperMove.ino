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
    for(int i = 0; i<60; i++)
    delay(1000);
    targetL = -targetL;
    targetR = -targetR;
    motors.setStepTarget( targetL, targetR);
  }
  motors.moveToTarget(1);
  while(1);
}
