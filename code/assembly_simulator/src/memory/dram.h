#include<stdlib.h>
#include<stdint.h>

#define MM_LEN 1000

// physical memory, we need to read the mm through functions, instead of directly
uint8_t mm[MM_LEN];

// virtual address = 0x0 -> 0xffffffffffff....
// physical address = 000 -> 999
// va -> pa, we can only read the data from physical memory
// '%' is not the real mapping method between virtual memory and physical memory

