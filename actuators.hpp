#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP

#include "config.hpp"

//{{{ class Sensor

class Sensor
{
	uint8_t sensing_pin;
	uint32_t value = 0;
	uint32_t sampling_period;
	uint32_t sampling_time = 0;
	virtual uint32_t measure(void) const
	{
		analogRead(sensing_pin);
	}
	virtual void process(uint32_t measure) = 0;
	public:
		virtual Sensor(uint8_t sensing_pin, uint32_t sampling_period) : sensing_pin(sensing_pin), sampling_period(sampling_period) {}
		uint32_t get_value(void)
		{
			return value;
		}
		void set_period(uint32_t period)
		{
			sampling_period = period;
		}
		uint32_t get_period(void)
		{
			return sampling_period;
		}

		virtual void operator()(const uint32_t current_time)
		{
			if( sampling_time+sampling_period <= current_time )
			{
				process(measure());
			}
		}
};
//}}}

//{{{ class Temp_sensor

class Temp_sensor: public Sensor
{
	uint32_t nominal_temperature;
	uint32_t temperature_plus_margin;
	uint32_t temperature_minus_margin;


	// Some stuff like an array for low-pass filtering, etc.

	uint32_t measure(void) const override  // The temperature sensor is measured differently
	{
		// TODO Read out the temperature sensor
	}

	void process(uint32_t measure)
	{
		// TODO filter
		// if it is too warm
		// fan.start()
	}

	public:
		Actuator heater;
		Actuator fan;

		Temp_sensor(uint8_t sensing_pin,
		            uint8_t heater_pin,
		            uint8_t fan_pin,
		            uint32_t sampling_period,
                    uint32_t nominal_temperature,
                    uint32_t temperature_plus_margin=0,
                    uint32_t temperature_minus_margin=0) :
			Sensor(sensing_pin, sampling_period),
			nominal_temperature(nominal_temperature),
			temperature_plus_margin(temperature_plus_margin?temperature_plus_margin:100),
			temperature_minus_margin(temperature_minus_margin?temperature_minus_margin:(temperature_plus_margin?temperature_plus_margin:100)),
			heater(heater_pin),
			fan(fan_pin)
			{}

		void set_nominal_temperature(uint32_t temperature)
		{
			nominal_temperature = temperature;
		}
		void set_plus_margin(uint32_t margin)
		{
			temperature_plus_margin = margin;
		}
		void set_minus_margin(uint32_t margin)
		{
			temperature_minus_margin = margin;
		}

		uint32_t get_nominal_temperature(void)
		{
			return nominal_temperature;
		}
		uint32_t get_plus_margin(void)
		{
			return temperature_plus_margin;
		}
		uint32_t get_minus_margin(void)
		{
			return temperature_minus_margin;
		}
};
//}}}


//{{{ class EC_sensor

class EC_sensor : public Sensor
{
	using Sensor::Sensor;
	// If we titrate the water, we'll add electrolytes.
	// Let's track their amount as a current offset
	// Static because offset will be the same for all sensors
	static int32_t current_offset;

	// Some stuff like an array for low-pass filtering, etc.

	void process(uint32_t measure)
	{
		// TODO filter
	}
	public:
		static void add_offset(int32_t offset)
		{
			current_offset += offset;
		}
		static void set_offset(int32_t offset)
		{
			current_offset = offset;
		}
		static int32_t get_offset(void)
		{
			return current_offset;
		}
};

int32_t EC_sensor::current_offset = 0;
//}}}

//{{{ class PH_sensor

class PH_sensor : public Sensor
{
	using Sensor::Sensor;
	// Some stuff like an array for low-pass filtering, etc.

	void process(uint32_t measure)
	{
		// TODO filter
		// if there is a change, inform the EC sensor of the offset
		// EC_sensor::add_offset(xxx);
	}
};
//}}}

#endif /* ACTUATORS_HPP */
