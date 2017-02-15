// Format:
//
//     |  cmd   | data[0]| data[1]| data[2]| data[3]|  crc   |
//



class Message_Interface
{
	using crc_sum = uint8_t;
	constexpr send_retries = 3;

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
	}
	//}}}

	//{{{
	struct message;
	{
		command cmd;
		uint32_t data;
		crc_sum crc;
	}  __attribute__((packed));
	//}}}

	//{{{
	uint32_t get_uint32_t(void)
	{
		uint32_t retval = 0;
		//while(Serial.available() < sizeof(retval));
		retval |= (static_cast<uint32_t>(Serial.read()))<<24;
		retval |= (static_cast<uint32_t>(Serial.read()))<<16;
		retval |= (static_cast<uint32_t>(Serial.read()))<< 8;
		retval |= (static_cast<uint32_t>(Serial.read()))<< 0;
		return retval;
	}
	//}}}

	//{{{ TODO abstract
	virtual void transmit_message(const message& msg) // must always succeed
	{
		size_t n = 0;
		while(n<sizeof(msg))	// Busy-loop until all data is force-fed into the UART
		{
			n += Serial.write(reinterpret_cast<const uint8_t*>(&msg) + n, sizeof(msg) - n)
		}
	}
	//}}}

	//{{{
	uint8_t send_ack(command cmd)
	{
		transmit_message({ command::ack; NULL; ack_crc; });
		return 0;	// the return value is for compound logic magic
	}
	//}}}

	//{{{
	uint8_t send_nack(command cmd)
	{
		transmit_message({ command::nack; NULL; nack_crc; });
		return 1;	// the return value is for compound logic magic
	}
	//}}}

	//{{{
	inline bool get_ack(command expected_cmd)
	{
		while(Serial.available() < sizeof(message));
		command cmd = Serial.read();
		switch(cmd)
		{
			case command::ack:
				(void) get_uint32_t(); // clear the data part
				return Serial.read() == ack_crc;
				break;
			case command::nack:
				(void) get_uint32_t(); // clear the data part
				(void) Serial.read();  // clear the crc part
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
		while(Serial.available() < sizeof(message));
		message msg;
		//uint32_t retval;
		uint8_t i=send_retries;
		do	// Read up to send_retries times until the command and crc are correct
		{	// On match send ACK, else send NACK
			msg.cmd = Serial.read();
			msg.data = get_uint32_t();
			msg.crc = Serial.read();
		} while((msg.cmd != expected_cmd || msg.crc != calc_src(msg.cmd, msg.data) || send_ack()) && send_nack() && --i)

		return i?msg.data:-1;
	}
	//}}}

	public:

	//{{{
#ifdef RASPI
	//{{{
	uint32_t get_temperature(void)
	{
		if(send_message(command::get_temperature, NULL)) return -1;
		return get_data(command::get_temperature);
	}
	//}}}
	//{{{
	uint32_t get_fan_status(void)
	{
		if(send_message(command::get_fan_status, NULL)) return -1;
		return get_data(command::get_fan_status);
	}
	//}}}
	//{{{
	uint32_t get_heater_status(void)
	{
		if(send_message(command::get_heater_status, NULL)) return -1;
		return get_data(command::get_heater_status);
	}
	//}}}
	//{{{
	uint32_t get_ph(void)
	{
		if(send_message(command::get_ph, NULL)) return -1;
		return get_data(command::get_ph);
	}
	//}}}
	//{{{
	uint32_t get_ec(void)
	{
		if(send_message(command::get_ec, NULL)) return -1;
		return get_data(command::get_ec);
	}
	//}}}
	//{{{
	uint32_t get_ec_offset(void)
	{
		if(send_message(command::get_ec_offset, NULL)) return -1;
		return get_data(command::get_ec_offset);
	}
	//}}}
	//{{{
	uint32_t get_lamp_status(void)
	{
		if(send_message(command::get_lamp_status, NULL)) return -1;
		return get_data(command::get_lamp_status);
	}
	//}}}
	//{{{
	uint32_t get_pump_status(void)
	{
		if(send_message(command::get_pump_status, NULL)) return -1;
		return get_data(command::get_pump_status);
	}
	//}}}
	
	//{{{
	bool set_temp_sensor_period(uint32_t period)
	{
		return send_message(command::set_temp_sensor_period, period);
	}
	//}}}
	//{{{
	bool set_nominal_temperature(uint32_t temp)
	{
		return send_message(command::set_nominal_temperature, temp);
	}
	//}}}
	//{{{
	bool set_temperature_margin_plus(uint32_t temp)
	{
		return send_message(command::set_temperature_margin_plus, temp);
	}
	//}}}
	//{{{
	bool set_ph_sensor_period(uint32_t period)
	{
		return send_message(command::set_ph_sensor_period, period);
	}
	//}}}
	//{{{
	bool set_ec_sensor_period(uint32_t period)
	{
		return send_message(command::set_ec_sensor_period, period);
	}
	//}}}
	//{{{
	bool set_ec_offset(uint32_t offset)
	{
		return send_message(command::set_ec_offset, offset);
	}
	//}}}
	//{{{
	bool add_ec_offset(uint32_t offset)
	{
		return send_message(command::add_ec_offset, offset);
	}
	//}}}
	//{{{
	bool set_lamp_period(uint32_t period)
	{
		return send_message(command::set_lamp_period, period);
	}
	//}}}
	//{{{
	bool set_lamp_duty_cycle(uint32_t duty_cycle)
	{
		return send_message(command::set_lamp_duty_cycle, duty_cycle);
	}
	//}}}
	//{{{
	bool set_pump_period(uint32_t period)
	{
		return send_message(command::set_pump_period, period);
	}
	//}}}
	//{{{
	bool set_pump_duty_cycle(uint32_t duty_cycle)
	{
		return send_message(command::set_pump_duty_cycle, duty_cycle);
	}
	//}}}
#endif
	//}}}

	//{{{
#ifdef ARDUINO
	//{{{
	void operator()(void)
	{
		while(Serial.available() > sizeof(message))
		{
			message msg = { Serial.read(), get_uint32_t(), Serial.read(), };
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
#endif
	//}}}


};

