// # htab_lookup_add.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"

htab_iterator_t htab_lookup_add(htab_t * t, const char *key){
    unsigned int hash = htab_hash_function(key);
    size_t index = hash % t->arr_size;
    struct htab_item * itemPtr = t->arr[index];
    // if there is no item
    if(!itemPtr){
        itemPtr = htab_item_init(key);
        // allocation failed
        if(!itemPtr) return htab_iterator_init(NULL, t, index);

        t->size++;
        t->arr[index] = itemPtr;
        return htab_iterator_init(itemPtr, t, index);
    }

    size_t itemKeyLength = 0;
    while(itemPtr->next != NULL){
        itemKeyLength = strlen(itemPtr->key);
        if(itemKeyLength == strlen(key) && strncmp(key, itemPtr->key, itemKeyLength) == 0)
             return htab_iterator_init(itemPtr, t, index);
        itemPtr = itemPtr->next;
    }
    itemKeyLength = strlen(itemPtr->key);
    if(itemKeyLength == strlen(key) && strncmp(key, itemPtr->key, itemKeyLength) == 0)
             return htab_iterator_init(itemPtr, t, index);

    struct htab_item *foo = htab_item_init(key);
    if(!foo) return htab_iterator_init(NULL, t, index);
    itemPtr->next = foo;
    t->size++;
    return htab_iterator_init(foo, t, index);
}