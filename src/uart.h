#ifndef UART_H
#define UART_H

#include "api.h"

// initialises the UART
void uart_init(void);

// reads an uint8 from UART
// returns null if nothing was read
uint8 uart_read(void);

// writes an uint8 into UART
void uart_write(uint8 c);

// writes a string (null terminated uint8 array) into UART
void uart_write_s(uint8* str);

#endif
