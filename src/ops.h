#ifndef OPS_H
#define OPS_H

#include "api.h"

// opcodes for the protocol
typedef enum
{
	// ignore
	ops_n,

	// bit 0
	ops_0,

	// bit 1
	ops_1,

	// begin
	ops_beg,

	// end
	ops_end,
	
	// count
	ops_count,		

	// pause
	ops_p
} ops;

#endif
