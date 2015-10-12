#include "ir.h"
#include "uart.h"
#include "ops.h"

// valid char range for sending
#define valid_char(c) (c >= 0x20 && c <= 0x7E)

// line buffer to store user input
static uint8 line[ir_line_size + 1];

// current line buffer index
static uint32 index;

// encode line into signals
static void encode(void);

void ir_write(void)
{
	uint8 read = uart_read();
	
	// no new char?
	if (!read) return;
	
	// not a line break?
	if (read != '\r')
	{
		if (read == 0x7F && index > 0)
		{
			line[--index] = 0;
			uart_write(read);
		}
		else if (index < ir_line_size && valid_char(read))
		{
			line[index++] = read;
			uart_write(read);
		}
		
		return;
	}
	
	// a line break but buffer is empty?
	if (index == 0) return;


	uart_write_s("\r\n");
	
	// null terminate it
	line[index] = 0;	
	// send it awaaaay!	
	encode();	
	// restart
	index = 0;
}

// automated testing
void ir_write_test(void)
{
	static const uint8 text[] = "Hello IR!";
	index = sizeof(text) - 1;
	memcpy(line, text, index);
	encode();
	sleep(1000000);
}

// reset write mode
void ir_reset_write(void)
{
	index = 0;

	// set terminal to blue
	uart_write_s("\x1B[36m");
}

__inline static void write_ops(ops value)
{
	// HIGH
	gpio_data(port_c) |= ir_out;
	sleep(ir_pulse_us * value);
	
	// LOW
	gpio_data(port_c) &= ~ir_out;
	sleep(ir_pulse_us);
}

static void encode(void)
{
	uint32 i;
	
	// start
	write_ops(ops_beg);
	
	for (i = 0; i < index; i++)
	{
		uint32 b = 8, c = line[i];		
		while (b--)
		{
			// toggle			
			write_ops(c & 0x1 ? ops_1 : ops_0);			
			c >>= 1;
		}	
	}	

	// end
	write_ops(ops_end);
}

