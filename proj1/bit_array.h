// # bit_array.h
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include <limits.h>
#include <stdlib.h>
#include "error.h"
#include <stdio.h>
#include <assert.h>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

typedef unsigned long bit_array_t[]; 

#define setbit(jmeno_pole, index, vyraz) \
        vyraz != 0 ? (jmeno_pole[(index)/ULONG_BIT] |=  (1UL << ((index)%ULONG_BIT))) :   \
                     (jmeno_pole[(index)/ULONG_BIT] &= ~(1UL << ((index)%ULONG_BIT))) 

#define getbit(jmeno_pole, index) ((jmeno_pole[((index)/ULONG_BIT)] & (1UL << ((index)%ULONG_BIT))) != 0)

#define ULONG_BIT (sizeof(unsigned long) * CHAR_BIT)

#define bit_array_create(jmeno_pole,velikost)_Static_assert(!(velikost <= 0), "Velikost pole nemuze byt mensi nebo rovno 0");\
                                             unsigned long  jmeno_pole [(velikost / ULONG_BIT) + \
                                            ((velikost %  ULONG_BIT) ? 1 : 0) + 1] = {velikost}; 

#define bit_array_alloc(jmeno_pole, velikost)                                    \
        assert(!(velikost <= 0)); \
        unsigned long *jmeno_pole = calloc(((velikost / ULONG_BIT) +            \
        ((velikost % ULONG_BIT) ? 1 : 0) + 1) , sizeof(unsigned long));                                     \
        if(jmeno_pole == NULL) {                                                 \
            fprintf(stderr, "bit_array_alloc: Chyba alokace pameti\n");          \
            return 1;                                                            \
        }                                                                        \
        *jmeno_pole = velikost;

#define bit_array_free(jmeno_pole)                                               \
        free(jmeno_pole);         
    
#ifndef USE_INLINE

    #define bit_array_size(jmeno_pole) jmeno_pole[0]

    #define bit_array_setbit(jmeno_pole, index, vyraz)                                                                          \
        if((unsigned long)index >= bit_array_size(jmeno_pole))                                                                  \
        error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)(jmeno_pole[0]-1));   \
        vyraz != 0 ? (jmeno_pole[((unsigned long)index)/ULONG_BIT + 1] |=  (1UL << (((unsigned long)index)%ULONG_BIT))) :   \
                     (jmeno_pole[((unsigned long)index)/ULONG_BIT + 1] &= ~(1UL << (((unsigned long)index)%ULONG_BIT))) 
 
    #define bit_array_getbit(jmeno_pole, index)                                                                                              \
        ((unsigned long)index >= bit_array_size(jmeno_pole)) ?                                                                                 \
        (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)(jmeno_pole[0]-1)), -1) :         \
        ((jmeno_pole[(((unsigned long)index)/ULONG_BIT) + 1] & (1UL << (((unsigned long)index)%ULONG_BIT))) != 0)

#else
    inline unsigned long bit_array_size(bit_array_t jmeno_pole){
        return jmeno_pole[0];
    }

    inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, const unsigned long index){
        if((index >= bit_array_size(jmeno_pole))) error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)(jmeno_pole[0]-1));

        return ((jmeno_pole[((index)/ULONG_BIT) + 1] & (1UL << ((index)%ULONG_BIT))) != 0);
    }

    inline void bit_array_setbit(bit_array_t jmeno_pole, const unsigned long index, const int vyraz){
        if((index >= bit_array_size(jmeno_pole))) error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)(jmeno_pole[0]-1));
        
        (vyraz != 0) ? (jmeno_pole[(index)/ULONG_BIT + 1] |=  (1UL << ((index)%ULONG_BIT))) : 
                       (jmeno_pole[(index)/ULONG_BIT + 1] &= ~(1UL << ((index)%ULONG_BIT)));
        return;
    }
#endif

#endif // for BIT_ARRAY_H