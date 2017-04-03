#include <iostream>
#include "message.hpp"



int main(void)
{
	//std::cout<<"Hello World!"<<std::endl;
	Message_interface arduino;

	for(uint32_t i=0; i<5; i++)
	{
		std::cout<<std::endl<<"==================="<<std::endl<<std::endl;
		uint32_t temp = arduino.get_temperature();
		std::cout<<"Temperature is: 0x"<<std::hex<<temp<<std::dec<<std::endl;

		std::cout<<std::endl<<"==================="<<std::endl;
		sleep(3);
	}




	//std::cout<<"Temperature is: "<<arduino.get_temperature()<<std::endl;



	return 0;
}
