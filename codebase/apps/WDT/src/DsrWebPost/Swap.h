#ifndef Swap_h
#define Swap_h

#include <stdint.h>

class Swap
{
    public:

        static void swap(uint32_t &a);

        static void swap(int32_t &a);

        static void swap(uint16_t &a);

        static void swap(int16_t &a);

        static void swap(float &a);

};

#endif
