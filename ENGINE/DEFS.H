#ifndef __DEFS_H
#define __DEFS_H

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;

typedef uint8_t byte_t;

typedef int8_t bool;
#define true (1)
#define false (0)

#define null (0)

#define vmin(a, b) (a < b ? a : b)
#define vmax(a, b) (a > b ? a : b)

struct InputFlag {
	enum Flags { None = 0, Pressed = (1 << 0), Released = (1 << 1) };
};

#endif
