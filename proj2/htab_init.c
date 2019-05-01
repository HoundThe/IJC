// # htab_init.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

htab_t *htab_init(size_t n){
    htab_t *table = malloc( sizeof(htab_t) + n * sizeof(struct htab_item*) );
    if(!table) return NULL;
    for(size_t i = 0; i < n; i++){
        table->arr[i] = NULL;
    }
    table->size = 0;
    table->arr_size = n;
    return table;
}