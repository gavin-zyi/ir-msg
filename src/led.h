#ifndef LED_H
#define LED_H

#include "api.h"

// Color constants
#define led_green	0x8
#define led_blue	0xC

// Initialises the LED
void led_init(void);

// Changes the LED to a specified color
void led_rgb(uint32 color);

#endif
