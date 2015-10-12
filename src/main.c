#include "api.h"
#include "uart.h"
#include "led.h"
#include "sw.h"
#include "ir.h"

// mode macros
#define read_mode	ir_read
#define write_mode	ir_write // change to ir_write_test for testing

// current mode
static action mode;

// sw1 press callback
static void change_mode(void);

int main(void)
{
	// setup hardware
	uart_init();
	ir_init();
	
	led_init();
	led_rgb(led_green);
	
	// assign and reset mode
	ir_reset(mode = read_mode);
	
	// register sw1 press event
	sw_init(sw_one, change_mode);
	
	// execute mode indefinitely
	while (1) mode();
}

// called when sw1 is pressed
static void change_mode(void)
{
	// toggle mode and LED
	
	if (mode == write_mode)
	{
		led_rgb(led_green);
		mode = read_mode;
	}
	else if (mode == read_mode)
	{
		led_rgb(led_blue);
		mode = write_mode;
	}
	
	// reset mode
	ir_reset(mode);
}
