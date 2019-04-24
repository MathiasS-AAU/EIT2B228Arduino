#include <AccelStepper.h>
class Stepper
{
	private:
	unsigned int maxSpeed = 1000; //Documentation says max is about 4000 for one stepper with a 16 MHz MCU
	unsigned int accelconst = 4; //time in seconds from point to point (if it works)
	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget(int8_t powerSave);
	void setCurrentStepPos(int stepPosL, int stepPosR);
	int *currentStepPos();
};
