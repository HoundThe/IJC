// # htab_iterator_get_value.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

int htab_iterator_get_value(htab_iterator_t it){
    return it.ptr->value;
}