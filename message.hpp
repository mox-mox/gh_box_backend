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
		uint32_t data[sizeof(uint32_t)]; // space for the command data and the CRC
		crc_sum crc;
	}  __attribute__((packed));
	//}}}

	//{{{
	uint32_t get_data(void)
	{
		uint32_t retval = 0;
		while(Serial.available() < sizeof(retval));
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
	uint8_t send_ack(command cmd)
	{
		transmit_message({ command::nack; NULL; nack_crc; });
		return 1;	// the return value is for compound logic magic
	}
	//}}}

	//{{{
	inline bool get_ack(command expected_cmd)
	{
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
	inline bool send_message(command cmd, uint32_t data)
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
		uint32_t retval;
		uint8_t i=send_retries;
		do	// Read up to send_retries times until the command and crc are correct
		{	// On match send ACK, else send NACK
			command cmd = Serial.read();
			retval = get_uint32_t();
			crc = Serial.read();
		} while((cmd != expected_cmd || crc != calc_src(cmd, retval) || send_ack()) && send_nack() && --i)

		return i?retval:-1;
	}
	//}}}


	public:

	








	//{{{
	virtual void send_get_ec_offset(void);

	virtual void send_ack(command cmd);
	virtual void send_nack(command cmd);

	virtual void send_set_status_period(uint32_t  period); // period in milliseconds
	virtual void send_set_status_period(uint32_t period);
	virtual void send_set_temp_sensor_period(uint32_t period);
	virtual void send_set_ph_sensor_period(uint32_t period);
	virtual void send_set_ec_sensor_period(uint32_t period);
	virtual void send_set_nominal_temperature(uint32_t temperature);//temperatureincentidegreescelsius
	virtual void send_set_temperature_margin_plus(uint32_t margin);
	virtual void send_set_temperature_margin_minus(uint32_t margin);
	virtual void send_set_ec_offset(int32_t offset);
	virtual void send_add_ec_offset(int32_t offset);
	virtual void send_set_pump_period(uint32_t period);
	virtual void send_set_pump_duty_cycle(uint32_t duty_cycle);
	virtual void send_set_lamp_period(uint32_t period);
	virtual void send_set_lamp_duty_cycle(uint32_t duty_cycle);
	//}}}






























































};

