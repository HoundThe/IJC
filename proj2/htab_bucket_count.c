// # htab_bucket_count.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}