//Serial library
#include <Comm.h>

//stepper library
#include <stepperLib.h>

//Serial library class
Comm SerialComm;

//stepper library class
Stepper motor;

void setup()
{  
	//Setup serial ports with settings for module 1 (Control module)
	SerialComm.setup(1); 
	
	//load last position from EEPROM
	motor.init();
	
	//Report ready to recieve commands
	SerialComm.sendResponse('R');
}

void loop()
{
	//Act on calibration switches
	motor.calSwitch();
	
	//Check command input
	char commandMsg = SerialComm.recieveCommand();
	
	//Check input for known commands
	switch (commandMsg)
	{
		case 'K': //Save current position and report status as ready for shutdown
			SerialComm.sendResponse('K');
			SerialComm.sendResponse('W');
			motor.shutdown();
			SerialComm.sendResponse('S');
		break;
		case 'A': //Go to point A
			SerialComm.sendResponse('A');
			SerialComm.sendResponse('W');
			motor.goTo(300,300); //Go to point A (X,Y) in mm
			SerialComm.sendResponse('R');
		break;
		case 'B': //Go to point B
			SerialComm.sendResponse('B');
			SerialComm.sendResponse('W');
			motor.goTo(300,700); //Go to point B (X,Y) in mm
			SerialComm.sendResponse('R');
		break;
		case 'C': //Go to point C
			SerialComm.sendResponse('C');
			SerialComm.sendResponse('W');
			motor.goTo(700,300); //Go to point C (X,Y) in mm
			SerialComm.sendResponse('R');
		break;
		case 'D': //Go to point D
			SerialComm.sendResponse('D');
			SerialComm.sendResponse('W');
			motor.goTo(700,700); //Go to point D (X,Y) in mm
			SerialComm.sendResponse('R');
		break;
		case 'E': //Go to calibration point
			SerialComm.sendResponse('E');
			SerialComm.sendResponse('W');
			motor.goToCal(); //Go to calibration point
			SerialComm.sendResponse('R');
		break;
	}
				
}
