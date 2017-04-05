#include <iostream>
#include "message.hpp"



int main(void)
{
	Message_interface arduino;

	for(uint32_t i=0; i<5; i++)
	{
		std::cout<<std::endl<<"==================="<<std::endl;
		std::cout<<"Values:"<<std::endl;
		std::cout<<"	Temperature is             : "<<static_cast<double>(arduino.get_temperature())/10<<std::endl;
		std::cout<<"	PH is                      : "<<static_cast<double>(arduino.get_ph())/100<<std::endl;
		//std::cout<<"	EC is                      : "<<arduino.get_ec()<<std::endl;
		//std::cout<<"	Pump is                    : "<<(arduino.get_pump_status()?"ON.":"OFF.")<<std::endl;
		//std::cout<<"	Heater is                  : "<<(arduino.get_heater_status()?"ON.":"OFF.")<<std::endl;
		//std::cout<<"	Fan is                     : "<<(arduino.get_fan_status()?"ON.":"OFF.")<<std::endl;
		//std::cout<<"	Lamp is                    : "<<(arduino.get_lamp_status()?"ON.":"OFF.")<<std::endl;
		//std::cout<<"Variables:"<<std::endl;
		//std::cout<<"	Temperature nominal is     : "<<static_cast<double>(arduino.get_temperature_nominal())/10<<"°C."<<std::endl;
		//std::cout<<"	Temperature plus margin is : "<<static_cast<double>(arduino.get_temperature_plus_margin())/10<<"°C."<<std::endl;
		//std::cout<<"	Temperature minus margin is: "<<static_cast<double>(arduino.get_temperature_minus_margin())/10<<"°C."<<std::endl;

		//std::cout<<"	EC offset is               : "<<static_cast<double>(arduino.get_ec_offset())/10<<"."<<std::endl;

		//std::cout<<"	Pump period is             : "<<static_cast<double>(arduino.get_pump_period())/1000<<"s."<<std::endl;
		//std::cout<<"	Pump duty cycle is         : "<<static_cast<double>(arduino.get_pump_duty_cycle())/1000<<"s."<<std::endl;
		//std::cout<<"	Lamp period is             : "<<static_cast<double>(arduino.get_lamp_period())/1000<<"s."<<std::endl;
		//std::cout<<"	Lamp duty cycle is         : "<<static_cast<double>(arduino.get_lamp_duty_cycle())/1000<<"s."<<std::endl;

		//std::cout<<"Please enter a new value for nominal temperature: ";
		//double new_temp; std::cin>>new_temp; std::cout<<std::endl;
		//std::cout<<"Setting value to "<<new_temp<<std::endl;
		//arduino.set_nominal_temperature(static_cast<uint32_t>(new_temp*10));


		std::cout<<std::endl<<std::endl;
		sleep(3);
	}







	return 0;
}
