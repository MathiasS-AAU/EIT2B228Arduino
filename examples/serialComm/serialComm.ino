//Serial library
#include <Comm.h>

//Serial library class
Comm SerialComm;

//Kill switch pin
#define KILLSWITCH 8

//Power state of control module. 1 is on, 0 is off.
int powerState = 1;

void setup()
{  
	//Setup serial ports with settings for module 1 (Control module)
	SerialComm.setup(0);
	
	//Define Kill Switch
	pinMode(KILLSWITCH,OUTPUT);
	
	//Turn on control module
	digitalWrite(KILLSWITCH, HIGH);
}

void loop()
{
	//Check command input
	char commandMsg = SerialComm.recieveCommand();
	
	//Check responce input
	char responceMsg = SerialComm.recieveResponse();
	
		//When control module reports ready to shut down, shut it down.
	if (responceMsg == 'S')//For echo(saying what command is executed) support shutdown response is now S
	{
		digitalWrite(KILLSWITCH, LOW);
		SerialComm.sendResponse("power off");
		SerialComm.sendResponse('R');
		powerState = 0;
	}
	//Check input for known commands
	switch (commandMsg)
	{
		//Send prepare to shutdown command
		case 'K':
			SerialComm.sendResponse('K');
			SerialComm.sendCommand(commandMsg);
		break;
		
		//Move to position. If shut down, turn on and send command when control module Reports status as ready.
		case 'A'...'E':
			if( powerState < 1)
			{
				powerState = 1;
				digitalWrite(KILLSWITCH, HIGH);
				SerialComm.sendResponse("power on");
				while(responceMsg != 'R')
				{
					responceMsg = SerialComm.recieveResponse();
				}
			}
			SerialComm.sendCommand(commandMsg);
		break;
		
		//Ignored formatting input
		case '\n':
		break;
		
		case '\r':
		break;
		
		case -1:
		break;
		
		//Invalid input
		default:
			SerialComm.sendResponse('F');
			SerialComm.sendResponse("unknown command: known commands are capitalized versions of {a, b, c, d, e, and k}");
		break;
	}
	
}
