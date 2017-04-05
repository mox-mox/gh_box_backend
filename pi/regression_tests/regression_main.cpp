#include "regression.hpp"
//#include <cstdint>
//#include <iostream>
//#include <ctype.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <termios.h>
//#include <string.h>
//#include <errno.h>



int main(void)
{
	if(!setup_uart())
	{
		return 1;
	}


	regress_get_temperature();


	std::cout<<"==============================="<<std::endl;
	while(1)
	{
		get_bytes(6);
		sleep(1);
	}

	close_uart();
}


