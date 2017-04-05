#include <cstdint>
#include <iostream>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

extern int uart0_filestream;

bool setup_uart(void);
void close_uart(void);

void write_bytes(unsigned char* tx_buffer, uint32_t length);
void get_bytes(uint8_t length=255);
void print_buffer(unsigned char* buffer, uint32_t length);


void regress_get_temperature(void);
