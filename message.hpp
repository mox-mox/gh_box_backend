#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#ifdef __AVR__
#include "config.hpp"
#endif

#ifdef __linux__
#include <cstdint>
#include <cstddef>
#endif

// Format:
//
//     |  cmd   | data[0]| data[1]| data[2]| data[3]|  crc   |
//


//{{{
class Message_interface_common
{
	protected:
	using crc_sum = uint8_t;
	static constexpr uint8_t send_retries = 3;
	protected:
		static constexpr uint32_t void_data = 0;
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
			message(command cmd, uint32_t data, crc_sum crc) : cmd(cmd), data(data), crc(crc) {}
			message() = default;
		}  __attribute__((packed));
		//}}}

		crc_sum calc_crc(command cmd, uint32_t data)
		{
			return 0; // TODO actual implementation
		}

		virtual uint8_t get_uint8_t(void) = 0;

		virtual uint32_t get_uint32_t(void) = 0;

		virtual void transmit_message(const message& msg) = 0; // must always succeed

		virtual uint8_t bytes_available(void) = 0;

		//{{{
		uint8_t send_ack(void)
		{
			transmit_message({command::ack, void_data, ack_crc});
			return 0;	// the return value is for compound logic magic
		}
		//}}}

		//{{{
		uint8_t send_nack(void)
		{
			transmit_message({command::nack, void_data, nack_crc});
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
				//default:
					//assert(false); // TODO: Better error handling
			}
			return false;
		}
		//}}}

		//{{{
		bool send_message(command cmd, uint32_t data)
		{
			//message msg = { cmd, data, calc_crc(cmd_data) };
			message msg(cmd, data, calc_crc(cmd, data));
			uint8_t i=send_retries;
			do // transmit up to send_retries times until we get an ACK
			{
				transmit_message(msg);
			} while(!get_ack(cmd) && --i);

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
				msg.cmd = static_cast < command > (get_uint8_t());
				msg.data = get_uint32_t();
				msg.crc = get_uint8_t();
			} while((msg.cmd != expected_cmd || msg.crc != calc_crc(msg.cmd, msg.data) || send_ack()) && send_nack() && --i);

			return i?msg.data:-1;
		}
		//}}}
};
//}}}


//{{{ class Message_interface
#ifdef  __linux__

class Message_interface : Message_interface_common
{
	//{{{
	inline uint8_t get_uint8_t(void) override
	{
		return 0;// TODO
	}
	//}}}
	//{{{
	uint32_t get_uint32_t(void) override
	{
		return 0;// TODO
	}
	//}}}
	//{{{
	void transmit_message(const message& msg) override // must always succeed
	{                                                  // This function must send the data bytes in reverse oder to account for the different endiannes
		// TODO
	}
	//}}}
	//{{{
	inline uint8_t bytes_available(void) override
	{
		return 0;// TODO
	}
	//}}}

	public:
	//{{{ Setters and Getters

	//{{{ Setters

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
	//}}}

	//{{{ Getters

	//{{{
	uint32_t get_temperature(void)
	{
		if(send_message(command::get_temperature, void_data)) return -1;
		return get_data(command::get_temperature);
	}
	//}}}
	//{{{
	uint32_t get_fan_status(void)
	{
		if(send_message(command::get_fan_status, void_data)) return -1;
		return get_data(command::get_fan_status);
	}
	//}}}
	//{{{
	uint32_t get_heater_status(void)
	{
		if(send_message(command::get_heater_status, void_data)) return -1;
		return get_data(command::get_heater_status);
	}
	//}}}
	//{{{
	uint32_t get_ph(void)
	{
		if(send_message(command::get_ph, void_data)) return -1;
		return get_data(command::get_ph);
	}
	//}}}
	//{{{
	uint32_t get_ec(void)
	{
		if(send_message(command::get_ec, void_data)) return -1;
		return get_data(command::get_ec);
	}
	//}}}
	//{{{
	uint32_t get_ec_offset(void)
	{
		if(send_message(command::get_ec_offset, void_data)) return -1;
		return get_data(command::get_ec_offset);
	}
	//}}}
	//{{{
	uint32_t get_lamp_status(void)
	{
		if(send_message(command::get_lamp_status, void_data)) return -1;
		return get_data(command::get_lamp_status);
	}
	//}}}
	//{{{
	uint32_t get_pump_status(void)
	{
		if(send_message(command::get_pump_status, void_data)) return -1;
		return get_data(command::get_pump_status);
	}
	//}}}
	//}}}
	//}}}
};
#endif
//}}}


//{{{ class Message_interface
#ifdef __AVR__

class Message_interface : public Message_interface_common
{
	//using Message_interface_common::Message_interface_common;
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
		const uint8_t* msg_arr = reinterpret_cast<const uint8_t*>(&msg);
		// Loop for each byte unitl it is really sent
		while(!Serial.write(msg_arr[0])); // Command
		while(!Serial.write(msg_arr[4])); // Data[3] Data is sent in
		while(!Serial.write(msg_arr[3])); // Data[2] reverse order to account
		while(!Serial.write(msg_arr[2])); // Data[1] for the different
		while(!Serial.write(msg_arr[1])); // Data[0] endianness of the host.
		while(!Serial.write(msg_arr[5])); // Checksum
	}
	//}}}
	//{{{
	inline uint8_t bytes_available(void) override
	{
		return Serial.available();
	}
	//}}}

	public:
	void test(void) // TODO: Remove
	{
		transmit_message({command::ack, 0x41424344, nack_crc});
	}

	//{{{
	void operator()(void)
	{
		while(bytes_available() > sizeof(message))
		{
			message msg(static_cast<command>(get_uint8_t()), get_uint32_t(), get_uint8_t());
			if(msg.crc != calc_crc(msg.cmd, msg.data) && send_nack())
			{
				continue;
			}
			send_ack();
			switch(msg.cmd)
			{
				//{{{ Getters
				case command::get_temperature:
					send_message(command::get_temperature, temp.get_value());
					break;
				case command::get_fan_status:
					send_message(command::get_fan_status, temp.fan.is_running());
					break;
				case command::get_heater_status:
					send_message(command::get_heater_status, temp.heater.is_running());
					break;

				case command::get_ph:
					send_message(command::get_ph, ph.get_value());
					break;

				case command::get_ec:
					send_message(command::get_ec, ec.get_value());
					break;
				case command::get_ec_offset:
					send_message(command::get_ec_offset, ec.get_offset());
					break;
				//}}}

				//{{{ Setters

				case command::set_temp_sensor_period:
					temp.set_period(msg.data);
					break;

				case command::set_nominal_temperature:
					temp.set_nominal_temperature(msg.data);
					break;
				case command::set_temperature_margin_plus:
					temp.set_plus_margin(msg.data);
					break;
				case command::set_temperature_margin_minus:
					temp.set_minus_margin(msg.data);
					break;
				case command::set_ph_sensor_period:
					ph.set_period(msg.data);
					break;
				case command::set_ec_sensor_period:
					ec.set_period(msg.data);
					break;
				case command::set_ec_offset:
					ec.set_offset(msg.data);
					break;
				case command::add_ec_offset:
					ec.add_offset(msg.data);
					break;
				case command::set_lamp_period:
					lamp.set_period(msg.data);
					break;
				case command::set_lamp_duty_cycle:
					lamp.set_duty_cycle(msg.data);
					break;
				case command::set_pump_period:
					pump.set_period(msg.data);
					break;
				case command::set_pump_duty_cycle:
					pump.set_duty_cycle(msg.data);
					break;
				//}}}

				//default:
					//assert(false); // TODO better error handling
			}
		}
	}
	//}}}
};
#endif
//}}}



#endif /* MESSAGE_HPP */
