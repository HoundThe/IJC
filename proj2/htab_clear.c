// # htab_clear.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

void htab_clear(htab_t * t){
    struct htab_item *item;
    struct htab_item *toFree;
    for(size_t i = 0; i < t->arr_size; i++){
        item = t->arr[i];
        while(item != NULL){
            toFree = item;
            item = item->next;
            free(toFree->key);
            free(toFree);
        }
        t->arr[i] = NULL;
    }
    t->size = 0;
}