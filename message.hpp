// Lets create a zero copy message passing protocol
//
//
// Format:
//	
//
//     | length | cmd    | data[0]|  ...   | data[n]|  crc   |
//
//
//
//



class Message
{

	public:
	//{{{
	enum class cmd : uint8_t
	{
		// Miscellaneous commands
		ack                          = 0,
		nack                         = 1,
	
		// Status commands
		set_status_intervall         = 10,
		send_status                  = 11,
	
		// Temp sensor commands
		set_temp_sensor_intervall    = 20,
		set_nominal_temperature      = 21,
		set_temperature_margin_plus  = 22,
		set_temperature_margin_minus = 23,
	
		// PH sensor commands
		set_ph_sensor_intervall      = 30,
		
		// EC sensor commands
		set_ec_sensor_intervall      = 40,
		get_ec_offset                = 41,
		set_ec_offset                = 42,
		add_ec_offset                = 43,
	
		// Pump commands
		set_pump_period              = 50,
		set_pump_duty_cycle          = 51,
	
		// Lamp commands
		set_lamp_period              = 60,
		set_lamp_duty_cycle          = 61,
	}
	//}}}







};

