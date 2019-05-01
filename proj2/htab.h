// # htab.h
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

// htab.h -- rozhraní knihovny htab (řešení IJC-DU2)
// Licence: žádná (Public domain)

// následující řádky zabrání násobnému vložení:
#ifndef __HTABLE_H__
#define __HTABLE_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool
#include <stdlib.h>     // malloc

// tabulka:
struct htab;    // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;     // typedef podle zadání
// iterátor do tabulky:
struct htab_item;               // neúplná deklarace struktury

// iterátor:
typedef struct htab_iterator {
    struct htab_item *ptr;      // ukazatel na položku
    const htab_t *t;            // ve které tabulce
    int idx;                    // ve kterém seznamu tabulky (TODO: optimalizovat?)
} htab_iterator_t;              // typedef podle zadání

// rozptylovací (hash) funkce
// pokud si v programu definujete stejnou funkci, použije se ta vaše
/**
 * @brief default hash function
 * 
 * @param str key to hash
 * @return unsigned int hash result
 */
unsigned int htab_hash_function(const char *str);


// funkce pro práci s tabulkou:
/**
 * @brief Allocates and initializes htab_t structure
 * 
 * @param n Size of the hash table array
 * 
 * @return htab_t* pointer to allocated structure, 
 *                 NULL if error
 */
htab_t *htab_init(size_t n);
/**
 * @brief Moves content from one Htab from another one, 
 *        clearing the source one
 * 
 * @param n Size of the new hash table
 * @param from Htable to move content from
 * @return htab_t* Pointer to new table
 */
htab_t *htab_move(size_t n, htab_t *from);
/**
 * @brief Returns amount of elements in the htab
 * 
 * @param t htab
 * @return size_t amount of elements 
 */
size_t htab_size(const htab_t * t);             // počet záznamů v tabulce
/**
 * @brief Returns array size of the htab
 * 
 * @param t htab
 * @return size_t Array size of the htab
 */
size_t htab_bucket_count(const htab_t * t);     // velikost pole
/**
 * @brief Adds element to the htab
 * 
 * @param t htab
 * @param key 
 * @return htab_iterator_t Iterator that points to the newly
 *                         added or existing element in htab
 */
htab_iterator_t htab_lookup_add(htab_t * t, const char *key);
/**
 * @brief Returns iterator to first item in htab
 * 
 * @param t htab
 * @return htab_iterator_t iterator to first item
 */
htab_iterator_t htab_begin(const htab_t * t);
/**
 * @brief 
 * 
 * @param t 
 * @return htab_iterator_t 
 */
htab_iterator_t htab_end(const htab_t * t);
/**
 * @brief Increment iterator the the next item
 * 
 * @param it iterator
 * @return htab_iterator_t iterator to next item or htab_end()
 */
htab_iterator_t htab_iterator_next(htab_iterator_t it);
/**
 * @brief Returns if the iterator is a valid one
 * 
 * @param it iterator
 * @return true Iterator is valid
 * @return false Iterator isn't valid
 */
static inline bool htab_iterator_valid(htab_iterator_t it) {
   return it.ptr!=NULL;
}
/**
 * @brief Returns true if iterators are equal
 * 
 * @param it1 
 * @param it2 
 * @return true 
 * @return false 
 */
static inline bool htab_iterator_equal(htab_iterator_t it1, htab_iterator_t it2) {
  return it1.ptr==it2.ptr && it1.t == it2.t;
}
/**
 * @brief Gets key from item that iterator points to
 * 
 * @param it iterator
 * @return const char* Key of the item iterator points to
 */
const char * htab_iterator_get_key(htab_iterator_t it);
/**
 * @brief Gets data from item that iterator points to
 * 
 * @param it iterator
 * @return int  
 */
int htab_iterator_get_value(htab_iterator_t it);
/**
 * @brief 
 * 
 * @param it 
 * @param val 
 * @return int 
 */
int htab_iterator_set_value(htab_iterator_t it, int val);
/**
 * @brief Clears all item from htab
 * 
 * @param t htab
 */
void htab_clear(htab_t * t);
/**
 * @brief Clears all item from htab and frees it
 * 
 * @param t htab
 */
void htab_free(htab_t * t);
#endif // __HTABLE_H__