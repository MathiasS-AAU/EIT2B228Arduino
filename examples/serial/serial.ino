#include <Comm.h>

Comm SerialComm;

#define KILLSWITCH 8

void setup()
{  
	SerialComm.setup(0);
}

void loop()
{
	int powerState;
	char commandMsg = SerialComm.recieveCommand();
	char responceMsg = SerialComm.recieveControl();
	
	switch (commandMsg)
	{
		case 'K':
		sendCommand(commandMsg);
		break;
		case 'A'...'D':
		if( powerState < 1;)
		{
			digitalWrite(KILLSWITCH, HIGH);
			while(responceMsg != 'R')
			{
				responceMsg = SerialComm.recieveControl();
			}
		}
		sendCommand(commandMsg);
		break;
	}
				
		if (responceMsg == 'K')
		{
			digitalWrite(KILLSWITCH, LOW);
			SerialComm.sendReponse("Shutdown");
			powerState = 0;
		}
		else
		{
			powerState = 1;
		}
}
