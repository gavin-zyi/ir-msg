#ifndef API_H
#define API_H

// typedefs for convenience
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;

// generic callback function type
typedef void (*action)(void);

// APIs for
// Stellaris LM4F120 LaunchPad Evaluation Kit

// GPIO ports
#define port_a				0x40004000
#define port_c				0x40006000
#define port_f				0x40025000

// UARTs
#define uart_0				0x4000C000

// system clock control
#define rcgc2				0xE108
#define rcguart				0xE618

void sysctrl(uint32 clock, uint32 port);

// GPIO APIs
#define gpio_data(port)		(*((uint32*) (port + 0x3FC)))
#define gpio_dir(port)		(*((uint32*) (port + 0x400)))

#define gpio_is(port)		(*((uint32*) (port + 0x404)))
#define gpio_ibe(port)		(*((uint32*) (port + 0x408)))
#define gpio_iev(port)		(*((uint32*) (port + 0x40C)))
#define gpio_im(port)		(*((uint32*) (port + 0x410)))
#define gpio_icr(port)		(*((uint32*) (port + 0x41C)))

#define gpio_afsel(port)	(*((uint32*) (port + 0x420)))

#define gpio_dr2r(port)		(*((uint32*) (port + 0x500)))
#define gpio_dr4r(port)		(*((uint32*) (port + 0x504)))
#define gpio_dr8r(port)		(*((uint32*) (port + 0x508)))

#define gpio_pur(port)		(*((uint32*) (port + 0x510)))
#define gpio_pdr(port)		(*((uint32*) (port + 0x514)))

#define gpio_den(port)		(*((uint32*) (port + 0x51C)))
#define gpio_pctl(port)		(*((uint32*) (port + 0x52C)))

// UART APIs
#define uart_data(uart)		(*((uint32*) (uart + 0x000)))
#define uart_flag(uart)		(*((uint32*) (uart + 0x018)))
#define uart_ibrd(uart)		(*((uint32*) (uart + 0x024)))
#define uart_fbrd(uart)		(*((uint32*) (uart + 0x028)))
#define uart_lcrh(uart)		(*((uint32*) (uart + 0x02C)))
#define uart_ctrl(uart)		(*((uint32*) (uart + 0x030)))

#define uart_im(uart)		(*((uint32*) (uart + 0x038)))
#define uart_icr(uart)		(*((uint32*) (uart + 0x044)))

// NVIC APIs
#define nvic_st_ctrl		(*((uint32*) 0xE000E010))
#define nvic_st_reload		(*((uint32*) 0xE000E014))
#define nvic_st_current		(*((uint32*) 0xE000E018))

#define nvic_en0			(*((uint32*) 0xE000E100))

#define nvic_sys_pri3		(*((uint32*) 0xE000ED20))

// misc. functions
__asm void sleep(uint32 us);

void memcpy(uint8* dst, const uint8* src, uint32 num);

__asm void cpsid(void);
__asm void cpsie(void);

#endif
