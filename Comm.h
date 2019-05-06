#include "Arduino.h"
class Comm 
{
	private:
		uint8_t module = 0;
	public:
		void setup(uint8_t device);
		void sendCommand(String buffer);
		void sendCommand(char buffer);
		char recieveCommand();
		void sendReponse(String buffer);
		void sendReponse(char buffer);
		char recieveReponse();
};
