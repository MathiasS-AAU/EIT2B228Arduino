#include <AccelStepper.h>
class Stepper
{
	private:
	unsigned int speedconst = 10;
	unsigned int accelconst = 100;
	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget();
};
