// # htab_end.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

htab_iterator_t htab_end(const htab_t * t){
    return htab_iterator_init(NULL, t, t->arr_size);
}