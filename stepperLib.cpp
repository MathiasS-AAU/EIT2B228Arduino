#include <stepperLib.h>

AccelStepper stepperL(AccelStepper::FULL4WIRE, 22, 24, 26, 28);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 48, 46, 44, 42);

//set target position
void Stepper::setStepTarget(int stepPosL, int stepPosR)
{  
    int distL = stepPosL;
    if (distL < 0) distL=distL*-1;  //distance must be positive
    stepperL.setMaxSpeed(Stepper::maxSpeed);
    stepperL.setAcceleration(Stepper::accelconst/(distL/100*distL/100)); //set acceleration in relation to distance
    //set movement target position
    stepperL.moveTo(stepPosL);

    int distR = stepPosR;
    if (distR < 0) distR=distR*-1;  //distance must be positive
    stepperR.setMaxSpeed(Stepper::maxSpeed);
    stepperR.setAcceleration(Stepper::accelconst/(distR/100*distR/100)); //set acceleration in relation to distance
    //set movement target position
    stepperR.moveTo(stepPosR);
}

//move to chosen target
void Stepper::moveToTarget()
{
  //enable stepper current
  stepperR.enableOutputs();
  stepperL.enableOutputs();
  
  //move to position
  while (stepperL.distanceToGo() != 0 && stepperR.distanceToGo() != 0)
  {
    //move towards position with chosen acceleration and speed
    stepperL.run();
    stepperR.run();
  }
  
  //disable stepper current
  stepperR.disableOutputs();
  stepperL.disableOutputs();
}
