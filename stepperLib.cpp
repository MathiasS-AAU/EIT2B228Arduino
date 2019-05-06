#include <stepperLib.h>
#include <EEPROM.h>
//if higher precision is needed, HALF4WIRE may be able to do half steps.
AccelStepper stepperL(AccelStepper::FULL4WIRE, 28, 26, 24, 22);
AccelStepper stepperR(AccelStepper::FULL4WIRE, 42, 44, 46, 48);

//set target position
void Stepper::setStepTarget(int stepPosL, int stepPosR)
{
  float distL = stepPosL;
  float distR = stepPosR;
  if (distL < 0) distL=distL*-1;  //distance must be positive
  if (distR < 0) distR=distR*-1;  //distance must be positive
  
  float distRatioL = stepPosL*1.0 / (stepPosL + stepPosR);
  float distRatioR = stepPosR*1.0 / (stepPosL + stepPosR);
  
  stepperL.setMaxSpeed(Stepper::maxSpeed*1.0*distRatioL);
  stepperL.setAcceleration((Stepper::maxSpeed/1.5)*distRatioL); //set acceleration in relation to distance and time
  //set movement target position
  stepperL.moveTo(stepPosL);

  stepperR.setMaxSpeed(Stepper::maxSpeed*1.0*distRatioR);
  stepperR.setAcceleration((Stepper::maxSpeed/1.5)*distRatioL); //set acceleration in relation to distance and time
  //set movement target position
  stepperR.moveTo(stepPosR);
  return;
}

//move to chosen target
void Stepper::moveToTarget(int8_t pwrSave)
{
  //enable stepper current
  stepperR.enableOutputs();
  stepperL.enableOutputs();

  //move to position
  while (stepperL.distanceToGo() != 0 || stepperR.distanceToGo() != 0) //.isRunning may fit better
  {
    //move towards position with chosen acceleration and speed
    stepperL.run();
    stepperR.run();
  }

  //disable stepper current
  if(pwrSave > 0)
  {
    stepperR.disableOutputs();
    stepperL.disableOutputs();
  }
  return;
}

//Set the position the stepper driver thinks it is in. UNTESTED
void Stepper::setCurrentStepPos(int stepPosL, int stepPosR)
{
  stepperL.setCurrentPosition(stepPosL);
  stepperR.setCurrentPosition(stepPosR);
  return;
}

void Stepper::resetCurrentStepPos()
{
  stepperL.setCurrentPosition(Stepper::calLenL);
  stepperR.setCurrentPosition(Stepper::calLenR);
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

void Stepper::shutdown()
{
  int pos[2];
  pos[0] = stepperL.currentPosition();
  pos[1] = stepperR.currentPosition();
  Serial.print("Saved LEFT: ");
  Serial.println(pos[0]);
  Serial.print("Saved RIGHT: ");
  Serial.println(pos[1]);
  EEPROM.put(0,pos);
  return;
}

void Stepper::init()
{
  int pos[2];
  EEPROM.get(0,pos);
  Serial.print("Loaded LEFT: ");
  Serial.println(pos[0]);
  Serial.print("Loaded RIGHT: ");
  Serial.println(pos[1]);
  stepperL.setCurrentPosition(pos[0]);
  stepperR.setCurrentPosition(pos[1]);
  return;
}

//Move to point
void Stepper::goTo(float X, float Y)
{
  float A = X-probeOffsetX;
  float B = Y-probeOffsetY;
  float b1 = sqrt(A*A+B*B);
  float b2 = sqrt((Stepper::grid_x-A)*(Stepper::grid_x-A)+B*B);
  Serial.println("Vi vil gerne til punkt");
  Serial.println(b1);
  Serial.println(b2);

  //Længde til nyt punkt
  Serial.println("Radius radius");
  int lStepLenToPoint = (b1)*Stepper::STEPS_PER_MM_L;
    Serial.println(lStepLenToPoint);
  Serial.println("paa motor L");
  int rStepLenToPoint = (b2)*Stepper::STEPS_PER_MM_R;
  Serial.println(rStepLenToPoint);
  Serial.println("paa motor R");

  //Set the stepper target
  Stepper::setStepTarget(lStepLenToPoint, rStepLenToPoint);
  //Move to target (maybe we should not call this here?)
  Stepper::moveToTarget(0);

  return;
}

void Stepper::goToCal()
{
  //Set the stepper target
  Stepper::setStepTarget(calLenL, calLenR);
  //Move to target (maybe we should not call this here?)
  Stepper::moveToTarget(0);

  return;
}


void Stepper::calSwitch()
{
  if(digitalRead(SW1) == HIGH || digitalRead(SW2) == HIGH)
  {
    stepperL.setMaxSpeed(100);
    stepperL.setAcceleration(400);
    stepperL.setCurrentPosition(0);
    stepperL.moveTo(999999);

    stepperR.setMaxSpeed(100);
    stepperR.setAcceleration(400);
    stepperR.setCurrentPosition(0);
    stepperR.moveTo(999999);

    while(digitalRead(SW1) == HIGH || digitalRead(SW2) == HIGH)
    {
      if(digitalRead(SW1) == HIGH) stepperL.run();
      if(digitalRead(SW2) == HIGH) stepperR.run();
    }

    stepperL.setCurrentPosition(Stepper::calLenL);
    stepperL.moveTo(Stepper::calLenL);

    stepperR.setCurrentPosition(Stepper::calLenR);
    stepperR.moveTo(Stepper::calLenR);
  }
}
