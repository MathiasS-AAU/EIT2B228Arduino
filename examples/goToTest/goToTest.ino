#include <stepperLib.h>

Stepper motors;

void setup()
{  
   Serial.begin(9600);
}

void loop()
{
  motors.goTo(98, 43);
  delay(1000);
  motors.goTo(40, 27);
  delay(1000);
  Serial.println("ny");
  delay(10000);
}
