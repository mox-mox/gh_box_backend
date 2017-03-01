#include "config.hpp"


//{{{ actuator.hpp

//{{{ class Actuator

//template < uint8_t control_pin >
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

//template < uint8_t control_pin >
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

//}}}


//{{{ sensor.hpp

//{{{ class Sensor

//template < uint8_t sensing_pin >
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
		Sensor(uint8_t sensing_pin, uint32_t sampling_period) : sensing_pin(sensing_pin), sampling_period(sampling_period) {}
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

//template < uint8_t sensing_pin, uint8_t heater_pin, uint8_t fan_pin >
class Temp_sensor: public Sensor
{
	//uint8_t heater_pin;
	//uint8_t fan_pin;
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
		//Actuator < heater_pin > heater;
		//Actuator < fan_pin > fan;

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

//template < uint8_t sensing_pin >
class EC_sensor : public Sensor
{
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
		//EC_sensor(uint8_t sensing_pin, uint32_t sensing_period) : Sensor(sensing_pin, sensing_period), current_offset(0) {}

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

template < uint8_t sensing_pin >
class PH_sensor : public Sensor
{
	// Some stuff like an array for low-pass filtering, etc.

	void process(uint32_t measure)
	{
		// TODO filter
		// if there is a change, inform the EC sensor of the offset
		// EC_sensor::add_offset(xxx);
	}
};
//}}}

//}}}


//{{{ message.hpp

// Format:
//
//     |  cmd   | data[0]| data[1]| data[2]| data[3]|  crc   |
//



class Message_interface
{
	using crc_sum = uint8_t;
	static constexpr uint8_t send_retries = 3;
	static constexpr crc_sum ack_crc = 0; // TODO
	static constexpr crc_sum nack_crc = 0; // TODO


	//{{{
	enum class command : uint8_t
	{
		// Miscellaneous commands
		ack                          =   0,	// |  ACK   |  zero  |  zero  |  zero  |  zero  |  crc   |
		nack                         = 255,	// |  NACK  |  zero  |  zero  |  zero  |  zero  |  crc   |

		// Getters: 	// get_temperature|NULL -> Arduino =======> get_temperature|VALUE -> Pi
		get_temperature              =  10,
		get_fan_status               =  11,
		get_heater_status            =  12,
		get_ph                       =  20,
		get_ec                       =  30,
		get_ec_offset                =  31,
		get_lamp_status              =  40,
		get_pump_status              =  50,

		// Setters
		// Temperature				// set_pump_period|PERIOD -> Arduino
		set_temp_sensor_period       = 110,
		set_nominal_temperature      = 113,
		set_temperature_margin_plus  = 114,
		set_temperature_margin_minus = 115,
		// PH sensor commands
		set_ph_sensor_period         = 120,
		// EC sensor commands
		set_ec_sensor_period         = 130,
		set_ec_offset                = 131,
		add_ec_offset                = 132,
		// Lamp commands
		set_lamp_period              = 140,
		set_lamp_duty_cycle          = 141,
		// Pump commands
		set_pump_period              = 150,
		set_pump_duty_cycle          = 151,
	};
	//}}}

	//{{{
	struct message
	{
		command cmd;
		uint32_t data;
		crc_sum crc;
	}  __attribute__((packed));
	//}}}


	virtual uint8_t get_uint8_t(void) = 0;

	virtual uint32_t get_uint32_t(void) = 0;

	virtual void transmit_message(const message& msg) = 0; // must always succeed

	virtual uint8_t bytes_available(void) = 0;

	//{{{
	uint8_t send_ack(command cmd)
	{
		transmit_message({ command::ack, NULL, ack_crc });
		return 0;	// the return value is for compound logic magic
	}
	//}}}

	//{{{
	uint8_t send_nack(command cmd)
	{
		transmit_message({ command::nack, NULL, nack_crc });
		return 1;	// the return value is for compound logic magic
	}
	//}}}

	//{{{
	inline bool get_ack(command expected_cmd)
	{
		while(bytes_available() < sizeof(message));
		command cmd = static_cast<command>(get_uint8_t());
		switch(cmd)
		{
			case command::ack:
				(void) get_uint32_t(); // clear the data part
				return get_uint8_t() == ack_crc;
				break;
			case command::nack:
				(void) get_uint32_t(); // clear the data part
				(void) get_uint8_t();  // clear the crc part
				break;
			default:
				assert(false); // TODO: Better error handling
		}
		return false;
	}
	//}}}

	//{{{
	bool send_message(command cmd, uint32_t data)
	{
		message msg = { cmd; data; calc_crc(cmd_data); };
		uint8_t i=send_retries;
		do // transmit up to send_retries times until we get an ACK
		{
			transmit_message(msg);
		} while(!get_ack(cmd) && --i)

		return i;
	}
	//}}}

	//{{{
	uint32_t get_data(command expected_cmd)
	{
		while(bytes_available() < sizeof(message));
		message msg;
		//uint32_t retval;
		uint8_t i=send_retries;
		do	// Read up to send_retries times until the command and crc are correct
		{	// On match send ACK, else send NACK
			msg.cmd = get_uint8_t();
			msg.data = get_uint32_t();
			msg.crc = get_uint8_t();
		} while((msg.cmd != expected_cmd || msg.crc != calc_src(msg.cmd, msg.data) || send_ack()) && send_nack() && --i)

		return i?msg.data:-1;
	}
	//}}}

};

//
////{{{ class Message
//#ifdef RASPI
//
//class Message : Message_interface
//{
//	//{{{
//	inline uint8_t get_uint8_t(void) override
//	{
//		return // TODO
//	}
//	//}}}
//	//{{{
//	uint32_t get_uint32_t(void) override
//	{
//		return // TODO
//	}
//	//}}}
//	//{{{
//	void transmit_message(const message& msg) override // must always succeed
//	{
//		// TODO
//	}
//	//}}}
//	//{{{
//	inline uint8_t bytes_available(void) override
//	{
//		return // TODO
//	}
//	//}}}
//
//
//	public:
//
//
//
//	//{{{
//	//{{{
//	uint32_t get_temperature(void)
//	{
//		if(send_message(command::get_temperature, NULL)) return -1;
//		return get_data(command::get_temperature);
//	}
//	//}}}
//	//{{{
//	uint32_t get_fan_status(void)
//	{
//		if(send_message(command::get_fan_status, NULL)) return -1;
//		return get_data(command::get_fan_status);
//	}
//	//}}}
//	//{{{
//	uint32_t get_heater_status(void)
//	{
//		if(send_message(command::get_heater_status, NULL)) return -1;
//		return get_data(command::get_heater_status);
//	}
//	//}}}
//	//{{{
//	uint32_t get_ph(void)
//	{
//		if(send_message(command::get_ph, NULL)) return -1;
//		return get_data(command::get_ph);
//	}
//	//}}}
//	//{{{
//	uint32_t get_ec(void)
//	{
//		if(send_message(command::get_ec, NULL)) return -1;
//		return get_data(command::get_ec);
//	}
//	//}}}
//	//{{{
//	uint32_t get_ec_offset(void)
//	{
//		if(send_message(command::get_ec_offset, NULL)) return -1;
//		return get_data(command::get_ec_offset);
//	}
//	//}}}
//	//{{{
//	uint32_t get_lamp_status(void)
//	{
//		if(send_message(command::get_lamp_status, NULL)) return -1;
//		return get_data(command::get_lamp_status);
//	}
//	//}}}
//	//{{{
//	uint32_t get_pump_status(void)
//	{
//		if(send_message(command::get_pump_status, NULL)) return -1;
//		return get_data(command::get_pump_status);
//	}
//	//}}}
//	
//	//{{{
//	bool set_temp_sensor_period(uint32_t period)
//	{
//		return send_message(command::set_temp_sensor_period, period);
//	}
//	//}}}
//	//{{{
//	bool set_nominal_temperature(uint32_t temp)
//	{
//		return send_message(command::set_nominal_temperature, temp);
//	}
//	//}}}
//	//{{{
//	bool set_temperature_margin_plus(uint32_t temp)
//	{
//		return send_message(command::set_temperature_margin_plus, temp);
//	}
//	//}}}
//	//{{{
//	bool set_ph_sensor_period(uint32_t period)
//	{
//		return send_message(command::set_ph_sensor_period, period);
//	}
//	//}}}
//	//{{{
//	bool set_ec_sensor_period(uint32_t period)
//	{
//		return send_message(command::set_ec_sensor_period, period);
//	}
//	//}}}
//	//{{{
//	bool set_ec_offset(uint32_t offset)
//	{
//		return send_message(command::set_ec_offset, offset);
//	}
//	//}}}
//	//{{{
//	bool add_ec_offset(uint32_t offset)
//	{
//		return send_message(command::add_ec_offset, offset);
//	}
//	//}}}
//	//{{{
//	bool set_lamp_period(uint32_t period)
//	{
//		return send_message(command::set_lamp_period, period);
//	}
//	//}}}
//	//{{{
//	bool set_lamp_duty_cycle(uint32_t duty_cycle)
//	{
//		return send_message(command::set_lamp_duty_cycle, duty_cycle);
//	}
//	//}}}
//	//{{{
//	bool set_pump_period(uint32_t period)
//	{
//		return send_message(command::set_pump_period, period);
//	}
//	//}}}
//	//{{{
//	bool set_pump_duty_cycle(uint32_t duty_cycle)
//	{
//		return send_message(command::set_pump_duty_cycle, duty_cycle);
//	}
//	//}}}
//	//}}}
//}
//#endif
////}}}
//

//{{{ class Message
//#ifdef ARDUINO

class Message : public Message_interface
{
	//{{{
	inline uint8_t get_uint8_t(void) override
	{
		return Serial.read();
	}
	//}}}
	//{{{
	uint32_t get_uint32_t(void) override
	{
		uint32_t retval = 0;
		//while(bytes_available() < sizeof(retval));
		retval |= (static_cast < uint32_t > (get_uint8_t()))<<24;
		retval |= (static_cast < uint32_t > (get_uint8_t()))<<16;
		retval |= (static_cast < uint32_t > (get_uint8_t()))<< 8;
		retval |= (static_cast < uint32_t > (get_uint8_t()))<< 0;
		return retval;
	}
	//}}}
	//{{{
	void transmit_message(const message& msg) override // must always succeed
	{
		size_t n = 0;
		while(n<sizeof(msg))	// Busy-loop until all data is force-fed into the UART
		{
			n += Serial.write(reinterpret_cast < const uint8_t* > (&msg) + n, sizeof(msg) - n)
		}
	}
	//}}}
	//{{{
	inline uint8_t bytes_available(void) override
	{
		return Serial.available();
	}
	//}}}

	public:


	//{{{
	void operator()(void)
	{
		while(bytes_available() > sizeof(message))
		{
			message msg = { get_uint8_t(), get_uint32_t(), get_uint8_t(), };
			if(msg.crc != calc_src(cmd, retval) && send_nack())
			{
				continue
			}
			send_ack();
			switch(msg.data)
			{
				//{{{ Getters
				case get_temperature:
					send_message(get_temperature, temp.get_value());
					break;
				case get_fan_status:
					send_message(get_fan_status, temp.fan.is_running());
					break;
				case get_heater_status:
					send_message(get_heater_status, temp.heater.is_running());
					break;

				case get_ph:
					send_message(get_ph, ph.get_value());
					break;

				case get_ec:
					send_message(get_ec, ec.get_value());
					break;
				case get_ec_offset:
					send_message(get_ec_offset, ec.get_offset());
					break;
				//}}}

				//{{{ Setters

				case set_temp_sensor_period:
					temp.set_period(msg.data);
					break;

				case set_nominal_temperature:
					temp.set_nominal_temperature(msg.data);
					break;
				case set_temperature_margin_plus:
					temp.set_plus_margin(msg.data);
					break;
				case set_temperature_margin_minus:
					temp.set_minus_margin(msg.data);
					break;
				case set_ph_sensor_periodriod:
					ph.set_period(msg.data);
					break;
				case set_ec_sensor_periodriod:
					ec.set_period(msg.data);
					break;
				case set_ec_offset:
					ec.set_offset(msg.data);
					break;
				case add_ec_offset:
					ec.add_offset(msg.data);
					break;
				case set_lamp_periodriod:
					lamp.set_period(msg.data);
					break;
				case set_lamp_duty_cycleriod:
					lamp.set_duty_cycle(msg.data);
					break;
				case set_pump_periodriod:
					pump.set_period(msg.data);
					break;
				case set_pump_duty_cycleriod:
					pump.set_duty_cycle(msg.data);
					break;
				//}}}

				default:
					assert(false); // TODO better error handling
			}
		}
	}
	//}}}
}
//#endif
//}}}


//}}}



//Periodic_actuator < PUMP_PIN >                        pump(PUMP_PERIOD, PUMP_DUTY_CYCLE);
//Periodic_actuator < LAMP_PIN >                        pump(LAMP_PERIOD, LAMP_DUTY_CYCLE);
//
//PH_sensor < PH_PIN >                                  ph(SAMPLING_PERIOD_PH);
//EC_sensor < EC_PIN >                                  ec(SAMPLING_PERIOD_EC);
//Temp_sensor < TEMP_PIN, HEATER_PIN, FAN_PIN >         temp(SAMPLING_PERIOD_TEMP, NOMINAL_TEMP, TEMP_MARGIN);


Periodic_actuator        pump(PUMP_PIN, PUMP_PERIOD, PUMP_DUTY_CYCLE);
Periodic_actuator        lamp(LAMP_PIN, LAMP_PERIOD, LAMP_DUTY_CYCLE);

PH_sensor                ph(PH_PIN, SAMPLING_PERIOD_PH);
EC_sensor                ec(EC_PIN, SAMPLING_PERIOD_EC);
Temp_sensor              temp(TEMP_PIN, HEATER_PIN, FAN_PIN, SAMPLING_PERIOD_TEMP, NOMINAL_TEMP, TEMP_MARGIN);

Message                  communicate;


void loop(void)
{
	// Create a timebase
	uint32_t current_time = millis();


	// Read the sensors
	//temp(); // Temperature sensor will also controll the radiator and fan
	//ph();
	//ec();

	temp.operator()(); // Temperature sensor will also controll the radiator and fan
	ph.operator()();
	ec.operator()();


	// See if we need to turn on the water pump or the lamp
	//pump();
	//lamp();

	pump.operator()();
	lamp.operator()();

}


void serialEvent()
{
	//communicate();
	communicate.operator()();
}
