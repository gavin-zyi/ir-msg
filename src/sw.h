#ifndef SW_H
#define SW_H

#include "api.h"

// switch structure
typedef volatile struct
{
	// port address
	uint32 port;
	// pin bits
	uint32 pin;
	// event handler
	action handler;
} sw_t;

// switch pointer
extern sw_t* sw_one;

// initialises the switch
// sw is the pointer to the switch
// handleris the event handler
void sw_init(sw_t* sw, action handler);

#endif
