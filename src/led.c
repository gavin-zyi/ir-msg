#include "led.h"

#define pins	0xE

void led_init(void)
{	
	// activate port f
	sysctrl(rcgc2, port_f);
	// output mode
	gpio_dir(port_f) |= pins;
	// regular gpio port
	gpio_afsel(port_f) &= ~pins;
	// 2ma current
	gpio_dr2r(port_f) |= pins;
	// digital mode
	gpio_den(port_f) |= pins;
	// clear all pins
	gpio_data(port_f) &= ~pins;
}

void led_rgb(uint32 color)
{
	// clear all pins
	gpio_data(port_f) &= ~pins;
	// set desired pins
	gpio_data(port_f) |= color;
}
