// # htab_item_get_key.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

const char * htab_iterator_get_key(htab_iterator_t it){
    return it.ptr->key;
}