#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/instruction.h"

static uint64_t decode_od(od_t od)
{
    if (od.type == IMM)
    {
        return od.imm;
    }
    else if (od.type == REG)
    {
        /*
        reg.rsp  0xabcd, 1  pmm[0xabcd] = 1  (physical memory)
        We need to return 0xabcd, instead of 0x1. We need to get the pointer,
        then decode.
        */
        return (uint64_t)od.reg1;
    }
    else
    {
        // mm
        uint64_t vaddr = 0;

        if (od.type == MM_IMM)
        {
            vaddr = *((uint64_t *)&od.imm);  // od.imm is int64_t, but return value is uint64_t
        }
        else if (od.type == MM_REG)
        {
            // store reg
            vaddr = *(od.reg1);
        }
        else if (od.type == MM_IMM_REG)
        {
            // store reg
            vaddr = od.imm + *(od.reg1);
        }
        else if (od.type == MM_REG1_REG2)
        {
            // store reg
            vaddr = *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_IMM_REG1_REG2)
        {
            // store reg
            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_REG2_S)
        {
            // store reg
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG2_S)
        {
            // store reg
            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_REG1_REG2_S)
        {
            // store reg
            vaddr = *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG1_REG2_S)
        {
            // store reg
            vaddr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scal;
        }

        return va2pa(vaddr);
    }
}

void instruction_cycle()
{
    inst_t *instr = (inst_t *)reg.rip;

    // imm: imm
    // reg: value
    // mm: paddr
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    // to operate the operator and operands, array of function pointers is needed
    // function_t func = function_table[instr->op];
    // func(src, dst);

    handler_t handler = handler_table[instr->op];

    handler(src, dst);

    printf("    %s\n", instr->code);
}

void init_handler_table()
{
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
    
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}



void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    /*
    add_reg_reg_handler(src = &rax, dst = &rbx)
    
    rax pmm[0x1234] = 0x1234000
    rbx pmm[0x1235] = 0xabcd

    src: 0x1234
    dst: 0x1235

    0x12340000 + 0xabcd = 0x1234abcd

    pmm[0x1235] = 0x1234abcd
    */
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}