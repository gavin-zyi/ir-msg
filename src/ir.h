#ifndef IR_H
#define IR_H

#include "api.h"

// pins
#define ir_out			(1 << 7)
#define ir_in			(1 << 6)

// pulse in us
#define ir_pulse_us		600
// sampling resolution
#define ir_pulse_res	10
// max line size for read/write
#define ir_line_size	20

// state constants
#define ir_on	1
#define ir_off	0


// initialises the IR
void ir_init(void);

// read mode function
void ir_read(void);
// write mode function
void ir_write(void);
// test write mode function
void ir_write_test(void);

// reset a mode
void ir_reset(action mode);

#endif
