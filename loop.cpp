#include "config.hpp"
#include "sensors.hpp"
#include "actuators.hpp"

Periodic_actuator<PUMP_PIN>                        pump(PUMP_PERIOD, PUMP_DUTY_CYCLE);
Periodic_actuator<LAMP_PIN>                        pump(LAMP_PERIOD, LAMP_DUTY_CYCLE);

PH_sensor<PH_PIN>                                  ph(SAMPLING_PERIOD_PH_SLOW);
EC_sensor<EC_PIN>                                  ec(SAMPLING_PERIOD_EC_SLOW);
Temp_sensor<TEMP_PIN, RADIATOR_PIN, FAN_PIN>       temp(SAMPLING_PERIOD_TEMP_SLOW, NOMINAL_TEMP, TEMP_MARGIN);


void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();


	temp();
	ph();
	ec();

	pump();
	lamp();
}
