#include <AccelStepper.h>
using namespace std;


class Stepper
{
  private:
		int pointA;
		int pointB;

		int start_x = 0;
		int start_y = 0;
		
		int grid_x = 100;
		int grid_y = 100;
		
  	float STEPS_PER_MM = 7;
  	
		unsigned int maxSpeed = 1000; //Documentation says max is about 4000 for one stepper with a 16 MHz MCU
		unsigned int accelconst = 4; //time in seconds from point to point (if it works)
	
		//Position of calibration point in relation to XY position of ring
		float mountCalPointX = 450-5.5; //450mm is half of the width of the box 5.5mm from wire mount
		float mountCalPointY = 40-5.5; //40mm offset from wooden bar 5.5mm from wire mount
		int probeOffsetX = 0;
		int probeOffsetY = 0;
		
		//Position of calibration point in relation to wire length from corner to mount ring
		int calLenL = sqrt(mountCalPointX*mountCalPointX+mountCalPointY*mountCalPointY)*STEPS_PER_MM;
		int calLenR = sqrt((grid_x-mountCalPointX)*(grid_x-mountCalPointX)+mountCalPointY*mountCalPointY)*STEPS_PER_MM;
	
	public:
		void calSwitch();
		void setStepTarget(int stepPosL, int stepPosR);
		void moveToTarget(int8_t powerSave);
		void setCurrentStepPos(int stepPosL, int stepPosR);
		int *currentStepPos();
		void goTo(int A, int B); //Fix variable names for clarification. Possibly use the stepper step variables for positional data.
};
