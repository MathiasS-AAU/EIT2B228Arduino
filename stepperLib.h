#include <AccelStepper.h>
using namespace std;

class Stepper
{
  private:
	unsigned int maxSpeed = 1000; //Documentation says max is about 4000 for one stepper with a 16 MHz MCU
	unsigned int accelconst = 4; //time in seconds from point to point (if it works)
  
  int pointA;
  int pointB;

  int grid_x = 100;
  int grid_y = 100;

  int start_x = 0;
  int start_y = 0;

  int STEPS_PER_MM = 7;

	public:
	void setStepTarget(int stepPosL, int stepPosR);
	void moveToTarget(int8_t powerSave);
	void setCurrentStepPos(int stepPosL, int stepPosR);
	int *currentStepPos();
  void goTo(int A, int B); //Fix variable names for clarification. Possibly use the stepper step variables for positional data.
};
