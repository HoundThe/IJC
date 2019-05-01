// # htab_item_init.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab_structs.h"

struct htab_item *htab_item_init(const char *key){
    struct htab_item *itemPtr = malloc(sizeof(struct htab_item));
    if(!itemPtr){
        return NULL;
    }
    size_t keyLength = strlen(key)+1;
    itemPtr->key = malloc(keyLength);
    memcpy(itemPtr->key, key, keyLength);
    itemPtr->next = NULL;
    itemPtr->value = 0; 
    return itemPtr;
}