// include guard to prevent double declaration of any identifiers
// such as types, enums and static variables
#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>

#define DEBUG_INSTRUCTIONCYCLE  0X1
#define DEBUG_REGISTERS         0X2
#define DEBUG_PRINTSTACK        0X4
#define DEBUG_PRINTCACHESET     0X8
#define DEBUG_CACHEDETAILS      0X10
#define DEBUG_MMU               0X20
#define DEBUG_LINKER            0X40
#define DEBUG_LOADER            0X80
#define DEBUG_PARSEINST         0X100

// to control the verbose degree of debug_printf
#define DEBUG_VERBOSE_SET       0X001

// do page walk
#define DEBUG_ENABLE_PAGE_WALK  0

// use sram cache for memory access
#define DEBUG_ENABLE_SRAM_CACHE 0

// printf wrapper
uint64_t debug_printf(uint64_t open_set, const char *format, ...);

// type converter
// uint32 to its equivalent float with rounding
uint32_t uint2float(uint32_t u);

// convert string dec or hex to the integer bitmap
uint64_t string2uint(const char *str);
uint64_t string2uint_range(const char *str, int start, int end);

#endif