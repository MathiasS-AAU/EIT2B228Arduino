#include <stepperLib.h>

Stepper motors;

void setup()
{  
   Serial.begin(9600);
}

void loop()
{
  motors.goTo(0, 50);
  delay(500);
  motors.goTo(50, 50);
  delay(500);
  motors.goTo(50, 0);
  delay(500);
  motors.goTo(0, 0);
  delay(500);
}
