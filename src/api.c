#include "api.h"

// system clock control (only used for activation)
void sysctrl(uint32 clock, uint32 port)
{
	uint32 val = 0;
	
	// get sysctrl register
	uint32* reg = ((uint32*) (0x400F0000 + clock));
	
	// calculate port number
	switch (port)
	{
		case port_a:
		case uart_0:
			val = 0x1;
			break;
		
		case port_c:
			val = 0x4;
			break;
		
		case port_f:
			val = 0x20;
			break;
	}
	
	// if not activated...
	if (!(*reg & val))
	{
		// activate
		*reg |= val;
		// sleep a bit
		sleep(1);
	}	
}

// clock = 16,000,000 cycles per sec
// therefore
//       = 16 cycles per 1.0000 us
//       = 1  cycle  per 0.0625 us (62.5 ns)
//
// function cycles 4 times per loop
// therefore
// 		 = 0.25 us per loop
//
// 4 loops = 0.25 us x 4 = 1 us
__asm void sleep(uint32 us)
{
	mov		r1, #4
	mul		r0, r1
proc
	nop
	subs	r0, #1;
	bne		proc;
	bx		lr;
}

// Copies the values of "num" bytes from the location
// pointed by "src" directly to the memory block
// pointed by "dst".
void memcpy(uint8* dst, const uint8* src, uint32 num)
{
	uint8* end = dst + num;
	while (dst < end)
	{
		*dst = *src;
		dst++;
		src++;
	}
}

// disable interrupt
__asm void cpsid(void)
{
	cpsid	I
}

// enable interrupt
__asm void cpsie(void)
{
	cpsie	I
}
