#include "config.hpp"
#include "sensors.hpp"
#include "actuators.hpp"








void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();

	static Temp_sensor temp(SAMPLING_PERIOD_TEMP_SLOW);
	static PH_sensor   ph(SAMPLING_PERIOD_PH_SLOW);
	static EC_sensor   ec(SAMPLING_PERIOD_EC_SLOW);
	static Pump        pump(PUMP_PERIOD, PUMP_DUTY_CYCLE);

	temp();
	ph();
	ec();

	pump();
}
