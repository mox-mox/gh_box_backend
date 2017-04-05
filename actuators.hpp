#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP

#include "config.hpp"

//{{{ class Actuator

class Actuator
{
	protected:
	uint32_t start_time = 0;

	private:
	uint8_t control_pin;
	bool running = false;

	inline void start_actuator(void)
	{
		digitalWrite(control_pin, 0);
	}
	inline void stop_actuator(void)
	{
		digitalWrite(control_pin, 1);
	}

	public:
		Actuator(uint8_t control_pin) : control_pin(control_pin) {}

		virtual void start(void)
		{
			//Serial.print("void start()\n");
			start_time = millis();
			running = true;
			start_actuator();
		}

		virtual void stop(void)
		{
			//Serial.print("             void stop()\n");
			stop_actuator();
			running = false;
		}

		inline bool is_running(void)
		{
			return running;
		}

		inline uint32_t get_start_time(void)
		{
			//Serial.print("get_start_time()\n");
			return start_time;
		}
};
//}}}


//{{{ class Periodic_actuator

class Periodic_actuator : public Actuator
{
	uint32_t period;
	uint32_t duty_cycle;

	public:
		Periodic_actuator(uint8_t control_pin, uint32_t period, uint32_t duty_cycle) :
			Actuator(control_pin),
			period(period),
			duty_cycle(duty_cycle)
		{
			if( duty_cycle >= period )
			{
				// TODO Send some error message
			}
			start();
		}

		void operator()(uint32_t current_time)
		{
			//Serial.print("current_time: ");
			//Serial.print(current_time);
			//Serial.print(", start_time: ");
			//Serial.print(get_start_time());
			//Serial.print(", start+period: ");
			//Serial.print(get_start_time()+period);
			//Serial.print(", start+duty: ");
			//Serial.print(get_start_time()+duty_cycle);
			if(!is_running()) // Should we start?
			{
				if(get_start_time()+period < current_time)
				{
					start();
					Serial.print("	Start\n");
				}
				else
				{
					Serial.print("	No Start\n");
				}
			}
			else
			{
				if(get_start_time()+duty_cycle < current_time)
				{
					stop();
					Serial.print("			Stop\n");
				}
				else
				{
					Serial.print("			No Stop\n");
				}

			}
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
