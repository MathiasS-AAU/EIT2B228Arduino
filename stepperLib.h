#include <AccelStepper.h>
class Stepper
{
	private:
	unsigned int maxSpeed = 1500; //Documentation says max is about 4000 for one stepper
	unsigned int accelconst = 100;
	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget();
	void setCurrentStepPos(int stepPosL, int stepPosR);
	int *Stepper::currentStepPos();
	void Stepper::setCurrentStepPos(int stepPosL, int stepPosR);
};
