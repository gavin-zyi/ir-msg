#include "sw.h"

static sw_t sws[] = {
	{port_f, 1 << 4, 0}
};

sw_t* sw_one = &sws[0];

void sw_init(sw_t* sw, action handler)
{	
	sw->handler = handler;
	
	// disable interrupt
	cpsid();
	
	// activate port
	sysctrl(rcgc2, sw->port);
	// input mode
	gpio_dir(sw->port) &= ~sw->pin;
	// regular gpio port
	gpio_afsel(sw->port) &= ~sw->pin;
	// pull up
	gpio_pur(sw->port) |= sw->pin;
	// 4ma current
	gpio_dr4r(sw->port) |= sw->pin;
	// digital mode
	gpio_den(sw->port) |= sw->pin;
	
	// interrupt setup
	gpio_is(sw->port) &= ~sw->pin;	
	gpio_ibe(sw->port) &= ~sw->pin;	
	gpio_iev(sw->port) &= ~sw->pin;	
	gpio_im(sw->port) |= sw->pin;
	
	nvic_en0 |= 1 << 30;
	
	// enable interrupt
	cpsie();
}

// invoked when sw1 is pressed, delegate the
// event to the handler if needed
__irq void sw_one_handler(void)
{
	// clear source
	gpio_icr(sw_one->port) |= sw_one->pin;
	
	// is the switch being pressed?
	if (!(gpio_data(sw_one->port) & sw_one->pin))
	{
		// invoke handler
		sw_one->handler();
	}
}


