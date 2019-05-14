#include <AccelStepper.h>
#define SW1 8
#define SW2 9
using namespace std;


class Stepper
{
  private:
		//????????????????????????
		int pointA;
		int pointB;

		//????????????????????????
		int startX = 0;
		int startY = 0;

		//Size of grid in mm
		float gridX = 982;
		float gridY = 985;

		//Radius conversion constants from mm to steps
  	float STEPS_PER_MM = 1000.0/((250+250)/2.0);//average 1000.0/((226.4+216.0)/2.0)
  	float STEPS_PER_MM_R = 1000.0/250;//right 1000.0/226.4;
  	float STEPS_PER_MM_L = STEPS_PER_MM_R;//1000.0/216.0;//left

  	//Max speed in steps per second
		float maxSpeed = 600; //Documentation says max is about 4000 for one stepper with a 16 MHz MCU

		//Mysterious acceleration constant used to time steppers to get to their point at the same time.
		float accelConst = 8; //time in seconds from point to point (if it works)

		//Position of calibration point in relation to XY position of mount point in mm.
		float mountCalPointX = 503-5; //503mm is half of the width of the box 5.5mm from wire mount
		float mountCalPointY = 663-5; //225mm offset from wooden bar 5.5mm from wire mount

		//Probe offset from mount point in mm
		int probeOffsetX = 0;
		int probeOffsetY = 55;
		int offSetY = -37;

		//Position of calibration point in relation to wire length from corner to mount ring in steps.
		int calLenL = 800*STEPS_PER_MM_L;
		int calLenR = 790*STEPS_PER_MM_R;

	//	int calLenL = sqrt(mountCalPointX*mountCalPointX+mountCalPointY*mountCalPointY)*STEPS_PER_MM_L;
	//	int calLenR = sqrt((gridX-mountCalPointX)*(gridX-mountCalPointX)+mountCalPointY*mountCalPointY)*STEPS_PER_MM_R;

	public:
		//When Left or right calibration buttons are presssed pull the left or right wire shorter with near constant speed, slight acceleration, and no deceleration.
		//When in position sets the current step position to (calLenL,calLenR).
		void calSwitch();

		//Set target to move to with acceleration where the point is in absolute steps. (NOT RELATIVE TO CURRENT POSITION)
		void setStepTarget(int stepPosL, int stepPosR);

		//Move with the acceleration calculated by setStepTarget to the target position. Powersave will shut motors down after use if the number is above 0
		void moveToTarget(int8_t powerSave);

		//Redefine the current position of the AccelStepper library in steps.
		void setCurrentStepPos(int stepPosL, int stepPosR);

		//Redefine the current position of the AccelStepper library as the calibration point.
		void resetCurrentStepPos();

		//Return the position AccelStepper library thinks it is in.[untested]
		int *currentStepPos();

		//Move to position using XY coordinates in mm. Function calculates the steps for AccelStepper library and uses setStepTarget and moveToTarget to move to the point.
		void goTo(float Xmm, float Ymm);

		//move to calibration point
		void goToCal();

		//
		void shutdown();

		//
		void init();
};
