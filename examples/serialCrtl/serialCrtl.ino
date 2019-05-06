#include <Comm.h>
#include <stepperLib.h>

Comm SerialComm;
Stepper motor;

void setup()
{  
	SerialComm.setup(1);
	motor.init();
	SerialComm.sendReponse('R');
}

void loop()
{
	motor.calSwitch();
	char commandMsg = SerialComm.recieveCommand();
	
	switch (commandMsg)
	{
		case 'K':
		motor.shutdown();
		SerialComm.sendReponse('K');
		break;
		case 'A':
		SerialComm.sendReponse('W');
		motor.goTo(300,300); //Go to point A (X,Y) in mm
		SerialComm.sendReponse('R');
		break;
		case 'B':
		SerialComm.sendReponse('W');
		motor.goTo(300,700); //Go to point B (X,Y) in mm
		SerialComm.sendReponse('R');
		break;
		case 'C':
		SerialComm.sendReponse('W');
		motor.goTo(700,300); //Go to point C (X,Y) in mm
		SerialComm.sendReponse('R');
		break;
		case 'D':
		SerialComm.sendReponse('W');
		motor.goTo(700,700); //Go to point D (X,Y) in mm
		SerialComm.sendReponse('R');
		break;
		case 'E':
		SerialComm.sendReponse('W');
		motor.goToCal(); //Go to calibration point
		SerialComm.sendReponse('R');
		break;
	}
				
}
