// # htab_move.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

htab_t *htab_move(size_t n, htab_t *from){
    htab_t * map = htab_init(n);
    if(!map){
        return NULL;
    }
    htab_iterator_t end = htab_end(from);
    for(htab_iterator_t i= htab_begin(from); i.idx != end.idx; i = htab_iterator_next(i)) {
       htab_iterator_t tmp =  htab_lookup_add(map, i.ptr->key);
       htab_iterator_set_value(tmp, i.ptr->value);
    }

    map->arr_size= n;
    map->size = from->size;

    htab_clear(from);

    return map;
}
