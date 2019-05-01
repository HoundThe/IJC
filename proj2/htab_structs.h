// # htab_structs.h
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#ifndef __HTABLE_STRUCTS_H__
#define __HTABLE_STRUCTS_H__

#include "htab.h"

struct htab_item{
    char *key;
    int value;
    struct htab_item *next;
};

struct htab{
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};


/**
 * @brief Allocates and initializes htab_item with a key
 * 
 * @param key 
 * @return struct htab_item* Pointer to new item
 */
struct htab_item *htab_item_init(const char *key);

/**
 * @brief Creates an iterator
 * 
 * @param ptr 
 * @param t 
 * @param idx 
 * @return htab_iterator_t 
 */
htab_iterator_t htab_iterator_init(struct htab_item * const ptr, const htab_t *t, const int idx);

#endif