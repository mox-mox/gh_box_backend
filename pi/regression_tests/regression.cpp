#include "regression.hpp"

int uart0_filestream = -1;

//{{{ Common functions

//{{{
bool setup_uart(void)
{
	//uart0_filestream = open("/dev/ttyAMA0", O_RDWR|O_NOCTTY|O_NDELAY);				//Open in non blocking read/write mode
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR|O_NOCTTY);
	if( uart0_filestream == -1 )
	{
		std::cout<<"Error - Unable to open UART.\n\tError message: "<<strerror(errno)<<std::endl;
		return false;
	}
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600|CS8|CLOCAL|CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
	return true;
}
//}}}

//{{{
void close_uart(void)
{
	close(uart0_filestream);
}
//}}}

//{{{
void write_bytes(unsigned char* tx_buffer, uint32_t length)
{
	int count = write(uart0_filestream, tx_buffer, length);
	std::cout<<"Wrote "; print_buffer(tx_buffer, count);
}
//}}}

//{{{
void get_bytes(uint8_t length)
{
	unsigned char rx_buffer[256];
	int rx_length = read(uart0_filestream, reinterpret_cast<void*>(rx_buffer), length);
	if( rx_length < 0 )
	{
		std::cout<<"Read error:\n\t"<<strerror(errno)<<std::endl;
	}
	else if( rx_length == 0 )
	{
		std::cout<<"No data received"<<std::endl;
	}
	else
	{
		rx_buffer[rx_length] = '\0';
		std::cout<<"Received "; print_buffer(rx_buffer, rx_length);
	}
}
//}}}

//{{{
void print_buffer(unsigned char* buffer, uint32_t length)
{
	std::cout<<"Buffer["<<length<<"] = { ";
	for(uint32_t i=0; i<length-1; i++)
	{
		//if(isprint(buffer[i]))
		if(isalpha(buffer[i]))
		{
			std::cout<<'\''<<buffer[i]<<"', ";
		}
		else
		{
			std::cout<<static_cast<uint32_t>(buffer[i])<<", ";
		}
	}
	//if(isprint(buffer[length-1]))
	if(isalpha(buffer[length-1]))
	{
		std::cout<<'\''<<buffer[length-1]<<"\' }"<<std::endl;;
	}
	else
	{
		std::cout<<static_cast<uint32_t>(buffer[length-1])<<" }"<<std::endl;
	}
}
//}}}

//}}}




//{{{
void regress_get_temperature(void)
{
	for(uint32_t i=0; i<5; i++)
	{
		std::cout<<"Get temperature: "<<std::endl;
		unsigned char tx_buffer[] = { 10, 0, 0, 0, 0, 0 };
		write_bytes(tx_buffer, sizeof(tx_buffer));

		sleep(1);
		std::cout<<"Expected frame:      { 0, 0, 0, 0, 0, 0 } // Ack"<<std::endl;
		get_bytes(6);
		std::cout<<std::endl;

		sleep(1);
		std::cout<<"Expected frame:      { 10, 0, 1, 226, 64, 0 } // Data"<<std::endl;
		get_bytes(6);
		std::cout<<std::endl;

		tx_buffer[0] = 0;
		write_bytes(tx_buffer, sizeof(tx_buffer));
		std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
		sleep(1);
	}
}
//}}}
