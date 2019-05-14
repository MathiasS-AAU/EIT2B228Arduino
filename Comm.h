#include "Arduino.h"
class Comm 
{
	private:
		//module number defined by setup function.
		uint8_t module = 0;
		
	public:
		//Setup serial ports with settings for module number. 0 is communications module and 1 is control module.
		void setup(uint8_t device);
		
		//Send command
		void sendCommand(String buffer);
		
		//Send command
		void sendCommand(char buffer);
		
		//Check command input
		char recieveCommand();
		
		//Send Response
		void sendResponse(String buffer);
		
		//Send Response
		void sendResponse(char buffer);
		
		//Check response input
		char recieveResponse();
};
