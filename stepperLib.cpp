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
  stepperL.setAcceleration(distL/(Stepper::accelconst*Stepper::accelconst)); //set acceleration in relation to distance and time
  //set movement target position
  stepperL.moveTo(stepPosL);

  int distR = stepPosR;
  if (distR < 0) distR=distR*-1;  //distance must be positive
  stepperR.setMaxSpeed(Stepper::maxSpeed);
  stepperR.setAcceleration(distR/(Stepper::accelconst*Stepper::accelconst)); //set acceleration in relation to distance and time
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
  while (stepperL.distanceToGo() != 0 && stepperR.distanceToGo() != 0) //.isRunning may fit better
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

//Get the position the stepper driver thinks it is in. UNTESTED
int *Stepper::currentStepPos()
{
  int pos[2];
  pos[0] = stepperL.currentPosition();
  pos[1] = stepperR.currentPosition();
  return pos;
}

//Move to point
void Stepper::goTo(int A, int B) 
{
  int a1 = sqrt(pow(Stepper::start_x, 2)+pow(Stepper::start_y, 2));
  int a2 = sqrt(pow(Stepper::grid_x-Stepper::start_x, 2)+pow(Stepper::start_y, 2));
  int b1 = sqrt(pow(A, 2)+pow(B, 2));
  int b2 = sqrt((Stepper::grid_x-A)*(Stepper::grid_x-A)+B*B);
  Serial.println("Vi kommer fra punkt");
  Serial.println(a1);
  Serial.println(a2);
  Serial.println("og vil gerne til punkt");
  Serial.println(b1);
  Serial.println(b2);
  
  int move_mL = (b1-a1)*Stepper::STEPS_PER_MM;
  int move_mR = (b2-a2)*Stepper::STEPS_PER_MM;
  Serial.println("For at gore dette, flytter vi");
  Serial.println(move_mL);
  Serial.println("paa motor L, og ");
  Serial.println(move_mR);
  Serial.println("paa motor R");
  
  //Set the stepper target
  Stepper::setStepTarget(move_mL, move_mR);
  //Move to target (maybe we should not call this here?)
  Stepper::moveToTarget(0);

  Stepper::start_x = A;
  Stepper::start_y = B;
  return;
}
#define SW1 8
#define SW2 9

void Stepper::calSwitch()
{
  if(digitalRead(SW1) == HIGH || digitalRead(SW2) == HIGH)
  {
    stepperL.setMaxSpeed(100);
    stepperL.setAcceleration(400);
    stepperL.setCurrentPosition(0);
    stepperL.moveTo(-999999);
    
    stepperR.setMaxSpeed(100);
    stepperR.setAcceleration(400);
    stepperR.setCurrentPosition(0);
    stepperR.moveTo(-999999);
    
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
