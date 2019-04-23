#include <AccelStepper.h>
class Stepper
{
	private:
	unsigned int maxSpeed = 1500; //Documentation says max is about 4000 for one stepper with a 16 MHz MCU
	unsigned int accelconst = 4; //time in seconds from point to point (if it works)
	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget();
	void setCurrentStepPos(int stepPosL, int stepPosR);
	int *Stepper::currentStepPos();
	void Stepper::setCurrentStepPos(int stepPosL, int stepPosR);
};
