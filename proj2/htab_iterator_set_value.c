// # htab_iterator_set_value.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab_structs.h"
#include "htab.h"

int htab_iterator_set_value(htab_iterator_t it, int val){
    it.ptr->value = val;
    return val;
}