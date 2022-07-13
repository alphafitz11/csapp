// include guard
#ifndef __MMU_H
#define __MMU_H

// memory management unit
#include <stdint.h>

uint64_t va2pa(uint64_t vaddr);

#endif