#include <AccelStepper.h>
class Stepper
{
	private:
	unsigned int maxSpeed = 10000;
	unsigned int accelconst = 100;
	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget();
};
