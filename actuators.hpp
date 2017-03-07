#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP

#include "config.hpp"

//{{{ class Actuator

class Actuator
{
	uint8_t control_pin;
	bool running = false;

	protected:
		inline void start_actuator(void)
		{
			digitalWrite(control_pin, 1);
		}
		inline void stop_actuator(void)
		{
			digitalWrite(control_pin, 0);
		}

	public:
		Actuator(uint8_t control_pin) : control_pin(control_pin) {}

		virtual void start(void)
		{
			//start_time = millis();
			running = true;
			start_actuator();
		}

		virtual void stop(void)
		{
			stop_actuator();
			running = false;
		}

		inline bool is_running(void)
		{
			return running;
		}
};
//}}}


//{{{ class Periodic_actuator

class Periodic_actuator : public Actuator
{
	uint32_t start_time = 0;

	uint32_t period;
	uint32_t duty_cycle;

	public:
		Periodic_actuator(uint8_t control_pin, uint32_t period, uint32_t duty_cycle) : Actuator(control_pin), period(period), duty_cycle(duty_cycle)
		{
			if( duty_cycle > period )
			{
				// TODO Send some error message
			}
			start();
		}

		virtual void operator()(const uint32_t current_time)
		{
			if(!is_running() && (start_time+period     <= current_time)) start_actuator();
			if( is_running() && (start_time+duty_cycle >= current_time)) stop_actuator();
		}

		void set_period(uint32_t period)
		{
			period = period;
		}
		uint32_t get_period(void)
		{
			return period;
		}

		void set_duty_cycle(uint32_t duty_cycle)
		{
			duty_cycle = duty_cycle;
		}
		uint32_t get_duty_cycle(void)
		{
			return duty_cycle;
		}
};
//}}}

#endif /* ACTUATORS_HPP */
