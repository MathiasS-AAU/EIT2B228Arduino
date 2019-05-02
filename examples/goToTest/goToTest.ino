#include <stepperLib.h>

Stepper motors;

void setup()
{  
   Serial.begin(9600);
   motors.resetCurrentStepPos();
}

void loop()
{
	for (int i = 0; i<2; i++)
	{
  delay(1000);
  motors.goTo(300, 300);
  delay(1000);
  motors.goTo(700, 300);
  delay(1000);
  motors.goTo(700, 700);
  delay(1000);
  motors.goTo(300, 700);
	}
  delay(1000);
  motors.goToCal();
  delay(2000);
}
