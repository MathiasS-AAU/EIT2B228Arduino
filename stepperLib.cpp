#include <stepperLib.h>
//if higher precision is needed, HALF4WIRE may be able to do half steps.
AccelStepper stepperL(AccelStepper::FULL4WIRE, 22, 24, 26, 28);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 48, 46, 44, 42);

//set target position
void Stepper::setStepTarget(int stepPosL, int stepPosR)
{  
  int distL = stepPosL;
  if (distL < 0) distL=distL*-1;  //distance must be positive
  stepperL.setMaxSpeed(Stepper::maxSpeed);
  stepperL.setAcceleration(Stepper::accelconst/(distL/100.0*distL/100.0)); //set acceleration in relation to distance
  //set movement target position
  stepperL.moveTo(stepPosL);

  int distR = stepPosR;
  if (distR < 0) distR=distR*-1;  //distance must be positive
  stepperR.setMaxSpeed(Stepper::maxSpeed);
  stepperR.setAcceleration(Stepper::accelconst/(distR/100.0*distR/100.0)); //set acceleration in relation to distance
  //set movement target position
  stepperR.moveTo(stepPosR);
  return;
}

//move to chosen target
void Stepper::moveToTarget()
{
  //enable stepper current
  stepperR.enableOutputs();
  stepperL.enableOutputs();
  
  //move to position
  while (stepperL.distanceToGo() != 0 && stepperR.distanceToGo() != 0) //.isRunning may fit better
  {
    //move towards position with chosen acceleration and speed
    stepperL.run();
    stepperR.run();
  }
  
  //disable stepper current
  stepperR.disableOutputs();
  stepperL.disableOutputs();
  return;
}

//Set the position the stepper driver thinks it is in. UNTESTED
void Stepper::setCurrentStepPos(int stepPosL, int stepPosR)
{
  stepperL.setCurrentPosition(stepPosL);
  stepperR.setCurrentPosition(stepPosR);
  return;
}

//Get the position the stepper driver thinks it is in. UNTESTED
int *Stepper::currentStepPos()
{
  int pos[2];
  pos[0] = stepperL.currentPosition();
  pos[1] = stepperR.currentPosition();
  return pos;
}
