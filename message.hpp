#ifndef MESSAGE_HPP
#define MESSAGE_HPP
extern int ledState;
#define ledPin 13		// the number of the LED pin

#ifdef __AVR__
#include "config.hpp"
#endif

#ifdef __linux__
#include <cstdint>
#include <cstddef>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <stdexcept>
#include <sys/ioctl.h>
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
		//static constexpr uint8_t send_retries = 3;
		static constexpr uint8_t send_retries = 1;
		static constexpr uint32_t void_data = 0;
		static constexpr crc_sum ack_crc = 0;	// TODO
		static constexpr crc_sum nack_crc = 128;	// TODO

		//{{{
		enum class command: uint8_t
		{
			// Miscellaneous commands
			ack                          =   0,	// |  ACK   |  zero  |  zero  |  zero  |  zero  |  crc   |
			nack                         = 255,	// |  NACK  |  zero  |  zero  |  zero  |  zero  |  crc   |

			// Getters:     // get_temperature|NULL -> Arduino =======> get_temperature|VALUE -> Pi
			get_temperature              =  10,
			get_fan_status               =  11,
			get_heater_status            =  12,
			get_temperature_nominal      =  13,
			get_temperature_plus_margin  =  14,
			get_temperature_minus_margin =  15,
			get_ph                       =  20,
			get_ec                       =  30,
			get_ec_offset                =  31,
			get_lamp_status              =  40,
			get_lamp_period              =  41,
			get_lamp_duty_cycle          =  42,
			get_pump_status              =  50,
			get_pump_period              =  51,
			get_pump_duty_cycle          =  52,

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
			message(command cmd, uint32_t data, crc_sum crc) : cmd(cmd), data(data), crc(crc) { }
			message() = default;
			//friend std::ostream& operator<<(std::ostream& lhs, message const& rhs)
			//{
			//	lhs<<"message { "<<static_cast<int>(rhs.cmd)<<", "<<rhs.data<<", "<<static_cast<int>(rhs.crc)<<" }";
			//	return lhs;
			//}
		}  __attribute__((packed));
		message read_message(void)
		{
			command cmd = static_cast<command>(get_uint8_t());
			uint32_t data = get_uint32_t();
			crc_sum crc = get_uint8_t();

			return {cmd, data, crc};
		}
		void fill_message(message& msg)
		{
			msg.cmd = static_cast<command>(get_uint8_t());
			msg.data = get_uint32_t();
			msg.crc = get_uint8_t();
		}

		//friend message read_message(void);
		//friend void fill_message(message& msg);
		//}}}

		crc_sum calc_crc(command cmd, uint32_t data)
		{
			(void) cmd;
			(void) data;
			return 253;	// TODO actual implementation
		}

		virtual uint8_t get_uint8_t(void) = 0;
		virtual bool put_uint8_t(uint8_t byte) = 0;

		//{{{
		uint32_t get_uint32_t(void)
		{
			uint32_t retval = 0;

			//while(bytes_available() < sizeof(retval));
			retval |= (static_cast < uint32_t > (get_uint8_t()))<<24;
			retval |= (static_cast < uint32_t > (get_uint8_t()))<<16;
			retval |= (static_cast < uint32_t > (get_uint8_t()))<<8;
			retval |= (static_cast < uint32_t > (get_uint8_t()))<<0;
			return retval;
		}
		//}}}

		void transmit_message(const message& msg)	// must always succeed
		{
			//std::cout<<"transmit_message("<<msg<<"):"<<std::endl;
			const uint8_t* msg_arr = reinterpret_cast<const uint8_t*>(&msg);

			// Loop for each byte unitl it is really sent
			while(!put_uint8_t(msg_arr[0])) ;	// Command
			//std::cout<<"	... "<<static_cast<int>(msg_arr[0])<<std::endl;
			while(!put_uint8_t(msg_arr[4])) ;	// Data[3] Data is sent in
			//std::cout<<"	... "<<static_cast<int>(msg_arr[4])<<std::endl;
			while(!put_uint8_t(msg_arr[3])) ;	// Data[2] reverse order to account
			//std::cout<<"	... "<<static_cast<int>(msg_arr[3])<<std::endl;
			while(!put_uint8_t(msg_arr[2])) ;	// Data[1] for the different
			//std::cout<<"	... "<<static_cast<int>(msg_arr[2])<<std::endl;
			while(!put_uint8_t(msg_arr[1])) ;	// Data[0] endianness of the host.
			//std::cout<<"	... "<<static_cast<int>(msg_arr[1])<<std::endl;
			while(!put_uint8_t(msg_arr[5])) ;	// Checksum
			//std::cout<<"	... "<<static_cast<int>(msg_arr[5])<<std::endl;

			//size_t n = sizeof(msg);
			//while(n)	// Busy-loop until all data is force-fed into the UART
			//{
			//	n -= Serial.write(msg_arr[n-1]);
			//}
		}

		virtual uint32_t bytes_available(void) = 0;
		//virtual void report_error(std::string error_message) = 0;
		virtual void report_error(const char* error_message) = 0;

		//{{{
		uint8_t send_ack(void)
		{
			//std::cout<<"send_ack()"<<std::endl;
			transmit_message({ command::ack, void_data, ack_crc });
			return 0;	// the return value is for compound logic magic
		}
		//}}}

		//{{{
		uint8_t send_nack(void)
		{
			//std::cout<<"send_nack()"<<std::endl;
			transmit_message({ command::nack, void_data, nack_crc });
			return 1;	// the return value is for compound logic magic
		}
		//}}}

		//{{{
		inline bool get_ack(command expected_cmd)
		{
			(void) expected_cmd;
			while( bytes_available() < sizeof(message)) ;

			//command cmd = static_cast < command > (get_uint8_t());

			message msg = read_message();
			//std::cout<<"get_ack(): received "<<msg<<std::endl;


			switch(msg.cmd)
			{
				case command::ack:
					return msg.crc == ack_crc;

					break;
				case command::nack:
					break;
				default:
					//report_error("Error: get_ack(): received command "+std::to_string(static_cast<int>(msg.cmd))+".");
					report_error("Error: get_ack(): received wrong command.");
			}
			return false;
		}
		//}}}

		//{{{
		bool send_message(command cmd, uint32_t data) // return false on failure
		{
			//std::cout<<"send_message( command cmd = "<<static_cast<int>(cmd)<<", uint32_t data = "<<data<<" )"<<std::endl;
			message msg(cmd, data, calc_crc (cmd, data));
			uint8_t i = send_retries;
			do	// transmit up to send_retries times until we get an ACK
			{
				//std::cout<<"send_message(): Sending "<<msg<<std::endl;
				transmit_message(msg);
			} while( !get_ack(cmd) && --i );
			if(i)
			{
				//std::cout<<"send_message(): ... message sent and ack'ed"<<std::endl;
			}
			else
			{
				//std::cout<<"send_message(): ... failed to send message"<<std::endl;
			}

			return i;
		}
		//}}}

		//{{{
		uint32_t get_data(command expected_cmd)
		{
			//std::cout<<"get_data( command expected_cmd = "<<static_cast<int>(expected_cmd)<<" )"<<std::endl;
			while( bytes_available() < sizeof(message)) ;
			message msg;
			//uint32_t retval;
			uint8_t i = send_retries;
			do	// Read up to send_retries times until the command and crc are correct
			{	// On match send ACK, else send NACK
				//msg.cmd = static_cast < command > (get_uint8_t());
				//msg.data = get_uint32_t();
				//msg.crc = get_uint8_t();
				fill_message(msg);
				//std::cout<<"get_data(): received "<<msg<<std::endl;
			} while((msg.cmd != expected_cmd || msg.crc != calc_crc(msg.cmd, msg.data) || send_ack()) && send_nack() && --i );
			//send_ack();

			return i ? msg.data : -1;
		}
		//}}}
};
//}}}


//{{{ class Message_interface for Raspberry Pi

#ifdef  __linux__

	class Message_interface: Message_interface_common
	{
		int uart0_filestream = -1;

		//{{{
		//void report_error(std::string error_message) override
		void report_error(const char* error_message) override
		{
			std::cerr<<error_message<<std::endl;
		}
		//}}}
		//{{{
		inline uint8_t get_uint8_t(void) override
		{
			uint8_t retval;
			while(1)
			switch(read(uart0_filestream, &retval, 1))
			{
				case 1:
					std::cout<<"					get_uint8_t() = "<<static_cast<int>(retval)<<std::endl;
					return retval;
					break;
				case 0:
					break;
				default:
					report_error(("Read error:\n\t"+std::string(strerror(errno))).c_str());
			}
		}
		//}}}

		//{{{
		bool put_uint8_t(uint8_t byte) override
		{
			while(1)
			switch(write(uart0_filestream, &byte, 1))
			{
				case 1:
					std::cout<<"							put_uint8_t( "<<static_cast<int>(byte)<<" )"<<std::endl;
					return true;
					break;
				case 0:
					break;
				default:
					report_error(("Write error:\n\t"+std::string(strerror(errno))).c_str());
			}
			return false;
		}
		//}}}

		//{{{
		inline uint32_t bytes_available(void) override
		{
			uint32_t bytes_avail;
			ioctl(uart0_filestream, FIONREAD, &bytes_avail);
			//std::cout<<"Please implement bytes_available(void)"<<std::endl;
			//return 0;	// TODO
			//std::cout<<"		There are now "<<bytes_avail<<" bytes available for reading"<<std::endl;
			//sleep(1);
			return bytes_avail;
		}
		//}}}

		public:
			//{{{
			Message_interface(void)
			{
				uart0_filestream = open("/dev/ttyAMA0", O_RDWR|O_NOCTTY);
				if( uart0_filestream == -1 )
					throw std::runtime_error("Error - Unable to open UART:\n\t"+std::string(strerror(errno)));
				struct termios options;
				tcgetattr(uart0_filestream, &options);
				options.c_iflag = IGNPAR;
				//options.c_iflag = PARMRK;
				options.c_cflag = B9600|CS8|CLOCAL|CREAD;
				options.c_oflag = 0;
				options.c_lflag = 0;
				tcflush(uart0_filestream, TCIFLUSH);
				tcsetattr(uart0_filestream, TCSANOW, &options);
			}
			//}}}
			//{{{ Setters and Getters

			//{{{ Setters Note: Return true means it worked

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

//
//			//{{{
//			uint32_t get_temperature(void)
//			{
//				//std::cout<<"	Trying to get temperature"<<std::endl;
//				if(!send_message(command::get_temperature, void_data))
//				{
//					std::cout<<"get_temperature(): Aborting"<<std::endl;
//					return -1;
//				}
//				//std::cout<<"	send request"<<std::endl;
//
//				uint32_t data = get_data(command::get_temperature);
//				for(uint32_t avail=bytes_available(); avail; avail--)
//				{
//					get_uint8_t();
//					//uint8_t byte = get_uint8_t();
//					//std::cout<<"remaining byte: "<<byte<<std::endl;
//				}
//
//				return data;
//			}
//			//}}}
//
			//{{{
			uint32_t get_temperature(void)
			{
				if(!send_message(command::get_temperature, void_data)) return -1;

				return get_data(command::get_temperature);
			}
			//}}}

			//{{{
			uint32_t get_temperature_nominal(void)
			{
				if(!send_message(command::get_temperature_nominal, void_data)) return -1;

				return get_data(command::get_temperature_nominal);
			}
			//}}}

			//{{{
			uint32_t get_temperature_plus_margin(void)
			{
				if(!send_message(command::get_temperature_plus_margin, void_data)) return -1;

				return get_data(command::get_temperature_plus_margin);
			}
			//}}}

			//{{{
			uint32_t get_temperature_minus_margin(void)
			{
				if(!send_message(command::get_temperature_minus_margin, void_data)) return -1;

				return get_data(command::get_temperature_minus_margin);
			}
			//}}}


			//{{{
			uint32_t get_fan_status(void)
			{
				if(!send_message(command::get_fan_status, void_data)) return -1;

				return get_data(command::get_fan_status);
			}
			//}}}
			//{{{
			uint32_t get_heater_status(void)
			{
				if(!send_message(command::get_heater_status, void_data)) return -1;

				return get_data(command::get_heater_status);
			}
			//}}}
			//{{{
			uint32_t get_ph(void)
			{
				if(!send_message(command::get_ph, void_data)) return -1;

				return get_data(command::get_ph);
			}
			//}}}
			//{{{
			uint32_t get_ec(void)
			{
				if(!send_message(command::get_ec, void_data)) return -1;

				return get_data(command::get_ec);
			}
			//}}}
			//{{{
			uint32_t get_ec_offset(void)
			{
				if(!send_message(command::get_ec_offset, void_data)) return -1;

				return get_data(command::get_ec_offset);
			}
			//}}}
			//{{{
			uint32_t get_lamp_status(void)
			{
				if(!send_message(command::get_lamp_status, void_data)) return -1;

				return get_data(command::get_lamp_status);
			}
			//}}}
			//{{{
			uint32_t get_lamp_period(void)
			{
				if(!send_message(command::get_lamp_period, void_data)) return -1;

				return get_data(command::get_lamp_period);
			}
			//}}}
			//{{{
			uint32_t get_lamp_duty_cycle(void)
			{
				if(!send_message(command::get_lamp_duty_cycle, void_data)) return -1;

				return get_data(command::get_lamp_duty_cycle);
			}
			//}}}
			//{{{
			uint32_t get_pump_status(void)
			{
				if(!send_message(command::get_pump_status, void_data)) return -1;

				return get_data(command::get_pump_status);
			}
			//}}}
			//{{{
			uint32_t get_pump_period(void)
			{
				if(!send_message(command::get_pump_period, void_data)) return -1;

				return get_data(command::get_pump_period);
			}
			//}}}
			//{{{
			uint32_t get_pump_duty_cycle(void)
			{
				if(!send_message(command::get_pump_duty_cycle, void_data)) return -1;

				return get_data(command::get_pump_duty_cycle);
			}
			//}}}
			//}}}
			//}}}
	};
#endif
//}}}


//{{{ class Message_interface for Arduino

#ifdef __AVR__

	class Message_interface: public Message_interface_common
	{
		//using Message_interface_common::Message_interface_common;
		//{{{
		//void report_error(std::string& error_message) override
		void report_error(const char* error_message) override
		{
			(void) error_message;
			digitalWrite(ledPin, 1);
		}
		//}}}
		//{{{
		inline uint8_t get_uint8_t(void) override
		{
			return Serial.read();
		}
		//}}}
		
		//{{{
		bool put_uint8_t(uint8_t byte) override
		{
			return Serial.write(byte);
		}
		//}}}


		//{{{
		inline uint32_t bytes_available(void) override
		{
			return Serial.available();
		}
		//}}}

		public:
			void test(void)	// TODO: Remove
			{
				transmit_message({ command::ack, 0x41424344, nack_crc });
			}

			//{{{
			void operator()(void)
			{
				while(bytes_available() >= sizeof(message))
				//while( bytes_available() >= 6 )
				{
					command cmd = static_cast < command > (get_uint8_t());
					uint32_t data = get_uint32_t();
					crc_sum crc = get_uint8_t();

					message msg(cmd, data, crc);


					if(msg.crc != calc_crc(msg.cmd, msg.data))
					{
						send_nack();
						continue;
					}

					send_ack();
					switch( msg.cmd )
					{
						//{{{ Getters
						case command::get_temperature:
							send_message(command::get_temperature, temp.get_value());
							break;
						case command::get_temperature_nominal:
							send_message(command::get_temperature_nominal, temp.get_nominal_temperature());
							break;
						case command::get_temperature_plus_margin:
							send_message(command::get_temperature_plus_margin, temp.get_plus_margin());
							break;
						case command::get_temperature_minus_margin:
							send_message(command::get_temperature_minus_margin, temp.get_minus_margin());
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

						case command::get_lamp_status:
							send_message(command::get_lamp_status, lamp.is_running());
							break;
						case command::get_lamp_period:
							send_message(command::get_lamp_period, lamp.get_period());
							break;
						case command::get_lamp_duty_cycle:
							send_message(command::get_lamp_duty_cycle, lamp.get_duty_cycle());
							break;

						case command::get_pump_status:
							send_message(command::get_pump_status, pump.is_running());
							break;
						case command::get_pump_period:
							send_message(command::get_pump_period, pump.get_period());
							break;
						case command::get_pump_duty_cycle:
							send_message(command::get_pump_status, pump.get_duty_cycle());
							break;
						//}}}

						//	//{{{ Setters

						//	case command::set_temp_sensor_period:
						//		temp.set_period(msg.data);
						//		break;

						//	case command::set_nominal_temperature:
						//		temp.set_nominal_temperature(msg.data);
						//		break;
						//	case command::set_temperature_margin_plus:
						//		temp.set_plus_margin(msg.data);
						//		break;
						//	case command::set_temperature_margin_minus:
						//		temp.set_minus_margin(msg.data);
						//		break;
						//	case command::set_ph_sensor_period:
						//		ph.set_period(msg.data);
						//		break;
						//	case command::set_ec_sensor_period:
						//		ec.set_period(msg.data);
						//		break;
						//	case command::set_ec_offset:
						//		ec.set_offset(msg.data);
						//		break;
						//	case command::add_ec_offset:
						//		ec.add_offset(msg.data);
						//		break;
						//	case command::set_lamp_period:
						//		lamp.set_period(msg.data);
						//		break;
						//	case command::set_lamp_duty_cycle:
						//		lamp.set_duty_cycle(msg.data);
						//		break;
						//	case command::set_pump_period:
						//		pump.set_period(msg.data);
						//		break;
						//	case command::set_pump_duty_cycle:
						//		pump.set_duty_cycle(msg.data);
						//		break;
						//	//}}}

						default:
							//assert(false); // TODO better error handling
							Serial.write("00000", 5);
					}
				}
			}
			//}}}
	};
#endif
//}}}



#endif /* MESSAGE_HPP */
