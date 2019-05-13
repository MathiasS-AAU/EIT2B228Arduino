#include <stepperLib.h>

Stepper motors;

void setup()
{  
	Serial.begin(9600);
}

void loop()
{
  motors.calSwitch();
}
