// # htab_iterator_init.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab_structs.h"

htab_iterator_t htab_iterator_init(struct htab_item * const ptr, const htab_t *t, const int idx){
    htab_iterator_t iterator;
    iterator.ptr = ptr;
    iterator.t = t;
    iterator.idx = idx;
    return iterator;
}