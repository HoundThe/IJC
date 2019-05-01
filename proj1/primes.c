// # primes.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include <stdlib.h>
#include <stdio.h>

#include "bit_array.h"
#include "eratosthenes.h"

#define ARR_SIZE (123000000)

int main(void){
    bit_array_create(bitArray, ARR_SIZE);
    unsigned long results[10];

    int toPrint = 0;
    Eratosthenes(bitArray);

    for(size_t i = ARR_SIZE-1; i > ARR_SIZE/2; i--){
        if((bit_array_getbit(bitArray, i) == 0)) {
            results[9-toPrint] = i;
            toPrint++;
            if(toPrint == 10) break;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%lu\n", results[i]);
    }
    
    return 0;
}