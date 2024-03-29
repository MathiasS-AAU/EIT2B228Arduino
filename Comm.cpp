#include <Comm.h>

void Comm::setup(uint8_t device)
{	
	Comm::module=device;
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
			Serial.begin(9600);
			Serial2.begin(9600);
			Serial.println("DEVICE 0: Communications Module");
		break;
	
		case 1://CtrlMod
			Serial.begin(9600);
			Serial3.begin(9600);
			Serial.println("DEVICE 1: Control Module");
		break;
	}
	return;
}

void Comm::sendCommand(String buffer)
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
		Serial2.println(buffer);
		break;
	}
	return;
}

void Comm::sendCommand(char buffer)
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
		Serial2.println(buffer);
		break;
	}
	return;
}

void Comm::sendResponse(String buffer)
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
		Serial.println(buffer);
		break;
		case 1://CtrlMod
		Serial3.println(buffer);
		break;
	}
	return;
}

void Comm::sendResponse(char buffer)
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
		Serial.println(buffer);
		break;
		case 1://CtrlMod
		Serial3.println(buffer);
		break;
	}
	return;
}

char Comm::recieveCommand()
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
		if(Serial.available())
		{
			char userInput = Serial.read();
			
			// Userinput debug for serialmonitor
			if (userInput != '\n' && userInput != '\r')
			{
				Serial.print("INPUT IS: ");
				Serial.println(userInput);
			}
			return userInput;
		}
		break;
	
		case 1://CtrlMod
		if(Serial3.available())
		{
			char commModuleInput = Serial3.read();
			
			// Userinput debug for serialmonitor
			if (commModuleInput != '\n' && commModuleInput != '\r')
			{
				Serial.print("INPUT IS: ");
				Serial.println(commModuleInput);
			}
			return commModuleInput;
		}
		break;
	}
	return -1;
}

char Comm::recieveResponse()
{
	//Check for module via module value
	switch (Comm::module)
	{
		case 0://CommMod
			if(Serial2.available())
			{
				char controlResponse = Serial2.read();
				// Userinput debug for serialmonitor
				if (controlResponse != '\n' && controlResponse != '\r' && controlResponse >= 'A' && controlResponse <= 'Z')
				{
					Serial.print("REPONSE IS: ");
					Serial.println(controlResponse);
				}
				else
				{
					Serial.print(controlResponse);
				}
				return controlResponse;
			}
			
		break;
	}
	return -1;
}
