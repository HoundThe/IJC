// # eratosthenes.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "bit_array.h"
#include <math.h>

void Eratosthenes(bit_array_t array){
    
    unsigned long condition = sqrt(bit_array_size(array));
    bit_array_setbit(array, 2, 0);
    bit_array_setbit(array, 1, 0);
     for(size_t j = 2*2; j < bit_array_size(array); j+=2) {
                bit_array_setbit(array, j, 1);
            }

    for(size_t i = 3; i < condition; i+=2) {
        if(bit_array_getbit(array, i) == 0) {
            for(unsigned long j = i*i; j < bit_array_size(array); j+= 2 * i) {
                bit_array_setbit(array, j, 1);
            }
        }
    }
}