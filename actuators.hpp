#ifndef ACTUATORS_HPP
#define ACTUATORS_HPP
//
//#include "config.hpp"
//
//
////{{{ class Actuator
//
//template<uint8_t control_pin>
//class Actuator
//{
//	bool running = false;
//
//	inline void start_actuator(void)
//	{
//		digitalWrite(control_pin, 1);
//	}
//	inline void stop_actuator(void)
//	{
//		digitalWrite(control_pin, 0);
//	}
//
//	public:
//		virtual void start(void)
//		{
//			start_time = millis();
//			running = true;
//			start_actuator();
//		}
//
//		virtual void stop(void)
//		{
//			stop_actuator();
//			running = false;
//		}
//
//		bool is_running(void)
//		{
//			return is_pumping;
//		}
//};
////}}}
//
//
////{{{ class Periodic_actuator
//
//template<uint8_t control_pin>
//class Periodic_actuator: Actuator
//{
//	uint32_t start_time = 0;
//
//	uint32_t period;
//	uint32_t duty_cycle;
//
//	public:
//		Periodic_actuator(uint32_t period, uint32_t duty_cycle) : period(period), duty_cycle(duty_cycle)
//		{
//			if( duty_cycle > period )
//			{
//				// TODO Send some error message
//			}
//			start();
//		}
//
//		virtual void operator()(const uint32_t current_time)
//		{
//			if( !is_pumping && (start_time+period     <= current_time)) start_pump();
//			if( is_pumping && (start_time+duty_cycle >= current_time)) stop_pump();
//		}
//
//		void set_period(uint32_t period)
//		{
//			period = period;
//		}
//		uint32_t get_period(void)
//		{
//			return period;
//		}
//
//		void set_duty_cycle(uint32_t duty_cycle)
//		{
//			duty_cycle = duty_cycle;
//		}
//		uint32_t get_duty_cycle(void)
//		{
//			return duty_cycle;
//		}
//};
////}}}
//
//

#endif /* ACTUATORS_HPP */
