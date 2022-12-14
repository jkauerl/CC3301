#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "concat.h"

uint concat_bits(uint x, int n, uint y, int m) {
// Ejemplo:: concat_bits(101, 2, 11001, 2)
//  101 -> 01 y 11001 -> 01
//  retorna 0101
// 
    unsigned i = -1;
    unsigned mask1 = ~(i<<n); // mask de x 0000000011111111111 con n 1
    unsigned mask2 = ~(i<<m); // mask de y

    mask1 = mask1 << m;
    x <<= m;

    x &= mask1;
    y &= mask2;
    x |= y;

    return x;
}

