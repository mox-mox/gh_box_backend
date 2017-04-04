#include <iostream>
#include "message.hpp"



int main(void)
{
	//std::cout<<"Hello World!"<<std::endl;
	Message_interface arduino;

	for(uint32_t i=0; true; i++)
	{
		////std::cout<<std::endl<<"==================="<<std::endl<<std::endl;
		//uint32_t temp = arduino.get_temperature();
		////std::cout<<"Temperature is: 0x"<<std::hex<<temp<<std::dec<<std::endl;
		//std::cout<<"Temperature is: 0x"<<std::dec<<temp<<std::dec<<std::endl;

		////std::cout<<std::endl<<"==================="<<std::endl;
		////sleep(3);
		
		std::cout<<std::endl<<"==================="<<std::endl;
		std::cout<<"Values:"<<std::endl;
		std::cout<<"	Temperature is             : "<<static_cast<double>(arduino.get_temperature())/10<<std::endl;
		std::cout<<"	PH is                      : "<<arduino.get_ph()<<std::endl;
		std::cout<<"	EC is                      : "<<arduino.get_ec()<<std::endl;
		std::cout<<"	Pump is                    : "<<(arduino.get_pump_status()?"ON.":"OFF.")<<std::endl;
		std::cout<<"	Heater is                  : "<<(arduino.get_heater_status()?"ON.":"OFF.")<<std::endl;
		std::cout<<"	Fan is                     : "<<(arduino.get_fan_status()?"ON.":"OFF.")<<std::endl;
		std::cout<<"Variables:"<<std::endl;
		std::cout<<"	Temperature nominal is     : "<<static_cast<double>(arduino.get_temperature_nominal())/10<<"s."<<std::endl;
		std::cout<<"	Temperature plus margin is : "<<static_cast<double>(arduino.get_temperature_plus_margin())/10<<"s."<<std::endl;
		std::cout<<"	Temperature minus margin is: "<<static_cast<double>(arduino.get_temperature_plus_margin())/10<<"s."<<std::endl;

		std::cout<<"	EC offset is               : "<<static_cast<double>(arduino.get_ec_offset())/10<<"s."<<std::endl;

		std::cout<<"	Pump period is             : "<<static_cast<double>(arduino.get_pump_period())/1000<<"s."<<std::endl;
		std::cout<<"	Pump duty cycle is         : "<<static_cast<double>(arduino.get_pump_duty_cycle())/1000<<"s."<<std::endl;
		std::cout<<"	Lamp period is             : "<<static_cast<double>(arduino.get_lamp_period())/1000<<"s."<<std::endl;
		std::cout<<"	Lamp duty cycle is         : "<<static_cast<double>(arduino.get_lamp_duty_cycle())/1000<<"s."<<std::endl;
		std::cout<<std::endl<<std::endl;
	}







	return 0;
}
