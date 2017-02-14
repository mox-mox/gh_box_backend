#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "config.hpp"
#include "actuators.hpp"

//{{{ Abstract
class Sensor
{
	uint32_t value = 0;
	uint32_t sampling_period;
	uint32_t sampling_time;
	virtual uint32_t measure(void) = 0;
	virtual void measure(uint32_t measure) = 0;
	public:
		virtual Sensor(uint32_t sampling_period) : sampling_period(sampling_period), sampling_time(millis()) {}
		void set_period(uint32_t period)
		{
			sampling_period = period;
		}
		uint32_t get_period(void)
		{
			return sampling_period;
		}

		virtual uint32_t get_value(void) const = 0;

		virtual void operator()(const uint32_t current_time)
		{
			if( sampling_time+sampling_period <= current_time )
			{
				process(measure());
			}
		}
}
//}}}

//{{{
class Temp_sensor: Sensor
{
	Actuator<RADIATOR_PIN> radiator;
	Actuator<FAN_PIN> fan;

	// Some stuff like an array for low-pass filtering, etc.

	uint32_t measure(void)
	{
		// TODO Do something
	}

	void process(uint32_t measure)
	{
		// TODO filter
	}

	public:
		uint32_t get_value(void) const
		{
			return value;
		}
}
//}}}

//{{{
class PH_sensor: Sensor
{
	// Some stuff like an array for low-pass filtering, etc.

	uint32_t measure(void)
	{
		// TODO Do something
	}

	void process(uint32_t measure)
	{
		// TODO filter
	}

	public:

		uint32_t get_value(void) const
		{
			return value;
		}
}
//}}}

//{{{
class EC_sensor: Sensor
{
	// Some stuff like an array for low-pass filtering, etc.

	uint32_t measure(void)
	{
		// TODO Do something
	}

	void process(uint32_t measure)
	{
		// TODO filter
	}

	public:

		uint32_t get_value(void) const
		{
			return value;
		}
}
//}}}

#endif /* SENSORS_HPP */
