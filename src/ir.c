#include "ir.h"

void ir_init(void)
{
	// activate port c
	sysctrl(rcgc2, port_c);
	
	// pc7 = out
	gpio_dir(port_c) |= ir_out;
	// pc6 = in
	gpio_dir(port_c) &= ~ir_in;
	
	// regular GPIO
	gpio_afsel(port_c) &= ~(ir_out | ir_in);
	
	// set current
	gpio_dr4r(port_c) |= ir_out;
	
	// set pull down
	gpio_pdr(port_c) |= ir_in;
	
	// enable digital
	gpio_den(port_c) |= ir_out | ir_in;
}

// declares private individual reset functions
void ir_reset_read(void);
void ir_reset_write(void);

void ir_reset(action mode)
{
	// invoke appropriate reset functions
	if (mode == ir_read)
	{
		ir_reset_read();
	}
	else if (mode == ir_write)
	{
		ir_reset_write();
	}
}
