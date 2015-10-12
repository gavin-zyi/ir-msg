#include "ir.h"
#include "ops.h"
#include "uart.h"

// timer stepping constant
#define step (ir_pulse_us / (ir_pulse_res + 5))

// sampling timer
static uint32 timer;
// sampling state
static uint32 state;

// sample an ops, returns ops_n if no ops is available
static ops sample(void);
// decode sampled time into an ops
static ops decode(uint8 mode, uint32 count);

void ir_read(void)
{
	// decoded char is in here
	static uint8 data;
	// tracks how many bits have passed
	static uint32 bit;
	// previous ops for error checking
	static ops prev;
	
	ops curr = sample();
	
	// ignore it
	if (curr == ops_n)
	{
		return;
	}
	
	// error checking
	if ((curr == ops_p && prev == ops_p) || (curr != ops_p && prev != ops_p))
	{
		// bad/corrupt format, so restart
		data = 0;
		bit = 1;	
	}
	else
	{
		// okay everything good to go
		// start processing the opcodes
		switch (curr)
		{
			case ops_1:
				data |= bit;
			case ops_0:
				bit <<= 1;
				break;
			
			case ops_beg:
				data = 0;
				bit = 1;			
				break;
			case ops_end:
				uart_write_s("\r\n");
				break;
		}
		
		// we have collected 8 bits, print them out
		if (bit == 256)
		{	
			uart_write(data);
			data = 0;
			bit = 1;
		}	
		
		prev = curr;
	}	
}

// reset read mode
void ir_reset_read(void)
{
	timer = 0;
	state = ir_off;

	// set terminal to green
	uart_write_s("\x1B[32m");
}

static ops sample(void)
{
	ops result = ops_n;
	
	// is signal HIGH?
	if ((gpio_data(port_c) & ir_in))
	{
		// has a change occured?
		if (state == ir_off)
		{
			// decode...
			result = decode('L', timer / step);
			timer = 0;
			state = ir_on;
		}
	}
	else // signal is LOW
	{
		// has a change occured?
		if (state == ir_on)
		{
			// decode...
			result = decode('H', timer / step);
			timer = 0;
			state = ir_off;
		}			
	}
	
	// increment timer
	// and sleep
	timer++;
	sleep(ir_pulse_res);

	return result;	
}

static ops decode(uint8 mode, uint32 count)
{
	switch (mode)
	{
		case 'H':
			if (count < ops_count)
			{
				return (ops) count;
			}
			break;
		case 'L':
			if (count == 1)
			{
				return ops_p;
			}
			break;
	}
	
	return ops_n;
}
