// # htab_begin.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

htab_iterator_t htab_begin(const htab_t * t){
    for(size_t i = 0; i < t->arr_size; i++){
        if(t->arr[i] != NULL) {
            return htab_iterator_init(t->arr[i], t, i);
        }
    }
    return htab_iterator_init(NULL, t, 0);
}