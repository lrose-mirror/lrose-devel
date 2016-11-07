#include "Swap.h"

void Swap::swap(uint32_t &a)
{
    asm volatile ("movl %1, %%eax;"
                  "bswap %%eax;"
                  "movl %%eax, %0;"
                  : "=r" ( a )
                  : "r" ( a )
                  : "%eax"
                  );
}

void Swap::swap(int32_t &a)
{
    asm volatile ("movl %1, %%eax;"
                  "bswap %%eax;"
                  "movl %%eax, %0;"
                   : "=r" ( a )
                   : "r" ( a )
                   : "%eax"
                 );
}

void Swap::swap(uint16_t &a)
{
    asm volatile ("movw %1, %%ax;"
                  "movw %1, %%bx;"
                  "shrw $0x08, %%ax;"
                  "shlw $0x08, %%bx;"
                  "andw $0x00FF, %%ax;"
                  "andw $0xFF00, %%bx;"
                  "orw %%bx, %%ax;"
                  "movw %%ax, %0;"
                  : "=r" ( a )
                  : "r" ( a )
                  : "%ax", "%bx"
                  );
}

void Swap::swap(int16_t &a)
{
    asm volatile ("movw %1, %%ax;"
                  "movw %1, %%bx;"
                  "shrw $0x08, %%ax;"
                  "shlw $0x08, %%bx;"
                  "andw $0x00FF, %%ax;"
                  "andw $0xFF00, %%bx;"
                  "orw %%bx, %%ax;"
                  "movw %%ax, %0;"
                  : "=r" ( a )
                  : "r" ( a )
                  : "%ax", "%bx"
                  );
}

void Swap::swap(float &a)
{
    asm volatile ("movl %1, %%eax;"
                  "bswap %%eax;"
                  "movl %%eax, %0;"
                  : "=r" ( a )
                  : "r" ( a )
                  : "%eax"
                  );
}
