#include "config.hpp"



Periodic_actuator        pump(PUMP_PIN, PUMP_PERIOD, PUMP_DUTY_CYCLE);
Periodic_actuator        lamp(LAMP_PIN, LAMP_PERIOD, LAMP_DUTY_CYCLE);

PH_sensor                ph(PH_PIN, SAMPLING_PERIOD_PH);
EC_sensor                ec(EC_PIN, SAMPLING_PERIOD_EC);
Temp_sensor              temp(TEMP_PIN, HEATER_PIN, FAN_PIN, SAMPLING_PERIOD_TEMP, NOMINAL_TEMP, TEMP_MARGIN);




Message                  communicate;

void setup(void)
{
	return;
}


void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();

	// Read the sensors
	temp(current_time); // Temperature sensor will also controll the radiator and fan
	ph(current_time);
	ec(current_time);

	// See if we need to turn on the water pump or the lamp
	pump(current_time);
	lamp(current_time);
	communicate.test();
	//communicate.send_message(Message::command::get_temperature, temp.get_value());
}


void serialEvent()
{
	communicate();
}
