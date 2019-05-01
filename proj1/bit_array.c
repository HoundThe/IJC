// # bit_array.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "bit_array.h"

#ifdef USE_INLINE

extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, const unsigned long index);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, const unsigned long index, const int vyraz);    

#endif //MACRO
