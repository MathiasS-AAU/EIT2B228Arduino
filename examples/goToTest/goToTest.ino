#include <stepperLib.h>

Stepper motors;

void setup()
{  
   Serial.begin(9600);
   motors.resetCurrentStepPos();
}

void loop()
{
  motors.goTo(489, 500);
  delay(10000);
  delay(10000);
  motors.goTo(489, 650);
  delay(10000);
  delay(10000);
  motors.goTo(600, 650);
  delay(10000);
  delay(10000);
  motors.goTo(600, 500);
  delay(10000);
  delay(10000);
}
