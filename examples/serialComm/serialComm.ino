#include <Comm.h>

Comm SerialComm;

#define KILLSWITCH 8

int powerState = 1;

void setup()
{  
	SerialComm.setup(0);
	pinMode(KILLSWITCH,OUTPUT);
	digitalWrite(KILLSWITCH, HIGH);
}

void loop()
{

	char commandMsg = SerialComm.recieveCommand();
	char responceMsg = SerialComm.recieveReponse();
	
	switch (commandMsg)
	{
		case 'K':
		SerialComm.sendCommand(commandMsg);
		break;
		case 'A'...'E':
		if( powerState < 1)
		{
			powerState = 1;
			digitalWrite(KILLSWITCH, HIGH);
			while(responceMsg != 'R')
			{
				responceMsg = SerialComm.recieveReponse();
			}
		}
		SerialComm.sendCommand(commandMsg);
		break;
	}
				
		if (responceMsg == 'K')
		{
			digitalWrite(KILLSWITCH, LOW);
			SerialComm.sendReponse('R');
			SerialComm.sendReponse("Shutdown");
			powerState = 0;
		}
}
