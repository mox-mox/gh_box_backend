#include "config.hpp"
#include "sensors.hpp"
#include "actuators.hpp"

Periodic_actuator<PUMP_PIN>                        pump(PUMP_PERIOD, PUMP_DUTY_CYCLE);
Periodic_actuator<LAMP_PIN>                        pump(LAMP_PERIOD, LAMP_DUTY_CYCLE);

PH_sensor<PH_PIN>                                  ph(SAMPLING_PERIOD_PH);
EC_sensor<EC_PIN>                                  ec(SAMPLING_PERIOD_EC);
Temp_sensor<TEMP_PIN, HEATER_PIN, FAN_PIN>         temp(SAMPLING_PERIOD_TEMP, NOMINAL_TEMP, TEMP_MARGIN);

Message                                            communicate;


void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();


	// Read the sensors
	temp(); // Temperature sensor will also controll the radiator and fan
	ph();
	ec();

	// See if we need to turn on the water pump or the lamp
	pump();
	lamp();

}


void serialEvent()
{
	communicate();
}
