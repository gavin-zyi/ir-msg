#include "uart.h"

// quick access to the 8 bit data section
// of the uart_data register
static uint8* data = ((uint8*) &uart_data(uart_0));

void uart_init()
{	
	// activate uart 0
	sysctrl(rcguart, uart_0);
	
	// activate port a
	sysctrl(rcgc2, port_a);
	
	// disable uart (UARTEN)
	uart_ctrl(uart_0) &= ~0x1;
	
	
	// set baud rates (115200) 
	// BRD	=	(sysclk / prescaler) / baudrate
	// 		=	(16M / 8) / 115200 
	// 		=	17.3611111 
	// IBRD	=	17
	// FBRD	=	round(64 * .3611111)
	//		=	23
	uart_ibrd(uart_0) = 17;
	uart_fbrd(uart_0) = 23;
	
	// 8 data bits, no parity, and 1 stop bit
	uart_lcrh(uart_0) = 0x60;
	
	// enable uart, rx, tx, prescaler=8 
	// UARTE=1, RxE=1, TxE=1, HSE=1 
	uart_ctrl(uart_0) |= 0x320;	
	uart_ctrl(uart_0) |= 0x1;
	
	// enable alt func
	gpio_afsel(port_a) |= 0x3;
	
	// enable digital i/o
	gpio_den(port_a) |= 0x3;
	
	// configure as UART
	gpio_pctl(port_a) |= 0x11;
}

uint8 uart_read(void)
{
	return ((uint8) uart_flag(uart_0)) & (1 << 4) ? 0 : *data;
}

void uart_write(uint8 c)
{
	while (((uint8) uart_flag(uart_0)) & (1 << 5));
	*data = c;
}

void uart_write_s(uint8* str)
{
	while (*str) uart_write(*str++);
}
