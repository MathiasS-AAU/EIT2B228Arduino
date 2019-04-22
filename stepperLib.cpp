#include <stepperLib.h>

AccelStepper stepperL(AccelStepper::FULL4WIRE, 22, 24, 26, 28);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 48, 46, 44, 42);

void Stepper::setStepTarget(int stepPosL, int stepPosR)
{  
    int distL = stepPosL;
    if (distL < 0) distL=distL*-1;
    stepperL.setMaxSpeed(distL*Stepper::speedconst);
    stepperL.setAcceleration(Stepper::accelconst/(distL/100*distL/100));
    stepperL.moveTo(stepPosL);

    int distR = stepPosR;
    if (distR < 0) distR=distR*-1;
    stepperR.setMaxSpeed(distR*Stepper::speedconst);
    stepperR.setAcceleration(Stepper::accelconst/(distR/100*distR/100));
    stepperR.moveTo(stepPosR);
}

void Stepper::moveToTarget()
{
  stepperR.enableOutputs();
  stepperL.enableOutputs();
  while (stepperL.distanceToGo() != 0 && stepperR.distanceToGo() != 0)
    {
      stepperL.run();
      stepperR.run();
    }
  stepperR.disableOutputs();
  stepperL.disableOutputs();
}
