#include <stdio.h>

#include "cpu/mmu.h"
#include "cpu/register.h"
#include "disk/elf.h"
#include "memory/dram.h"
#include "memory/instruction.h"

uint64_t add(uint64_t a, uint64_t b)
{
    uint64_t c = a + b;
    return c;
}


int main()
{
    // uint64_t a = 0x12340000;
    // uint64_t b = 0x0000abcd;
    // uint64_t c = add(a, b);

    // register function pointers
    init_handler_table();

    // init the register state before "mov \%rdx, \%rsi"
    reg.rax = 0x12340000;
    reg.rbx = 0x8001190;
    reg.rcx = 0x8001190;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee2c8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee1d0;
    reg.rsp = 0x7ffffffee1b0;

    reg.rip = (uint64_t)&program[11];

    // init memory state with stack format
    write64bits_dram(va2pa(0x7ffffffee1d0), 0x0);  // rbp, top of stack
    write64bits_dram(va2pa(0x7ffffffee1c8), 0x0);
    write64bits_dram(va2pa(0x7ffffffee1c0), 0x0000abcd);
    write64bits_dram(va2pa(0x7ffffffee1b8), 0x12340000);
    write64bits_dram(va2pa(0x7ffffffee1b0), 0x0);  // rsp, bottom of stack

    print_register();
    print_stack();

    // run inst
    for (int i = 0; i < 1; i ++)
    {
        instruction_cycle();
        
        print_register();
        print_stack();
    }

    // verify: compare the registers and the stack memory with the real values
    uint8_t match = 1;

    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x8001190);
    match = match && (reg.rcx == 0x8001190);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee1d0);
    match = match && (reg.rsp == 0x7ffffffee1b0);

    if (match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (read64bits_dram(va2pa(0x7ffffffee1d0)) == 0x0);  // rbp, top of stack
    match = match && (read64bits_dram(va2pa(0x7ffffffee1c8)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1c0)) == 0x0000abcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1b8)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1b0)) == 0x0);  // rsp, bottom of stack    

    if (match == 1)
    {
        printf("memory match\n");
    }
    else
    {
        printf("memory not match\n");
    }

    return 0;
}

