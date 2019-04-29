#include <stepperLib.h>

Stepper motors;
int targetL = -1000;
int targetR = -1000;

void setup()
{  
  motors.setStepTarget( targetL, targetR);
}

void loop()
{
    for(int i = 0; i<10; i++)
  {
    motors.moveToTarget(0);
    delay(100000);
    motors.setStepTarget( targetL, targetR);
  }
  motors.moveToTarget(1);
  while(1);
}
