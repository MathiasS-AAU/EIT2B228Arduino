#include <stepperLib.h>

Stepper motors;

void setup()
{  
   Serial.begin(9600);
   motors.resetCurrentStepPos();
}

void loop()
{
  motors.goTo(800, 650);
  delay(10000);
  delay(10000);
  motors.goTo(600, 650);
  delay(10000);
  delay(10000);
  motors.goTo(600, 850);
  delay(10000);
  delay(10000);
  motors.goTo(800, 850);
  delay(10000);
  delay(10000);
}
