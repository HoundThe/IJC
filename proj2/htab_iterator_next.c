// # htab_iterator_next.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "htab.h"
#include "htab_structs.h"


htab_iterator_t htab_iterator_next(htab_iterator_t it){
    // if it points to the last element of index
   if(it.ptr->next == NULL){
       for(size_t i = it.idx + 1; i < it.t->arr_size; i++){
           if(it.t->arr[i] != NULL){
               it.ptr = it.t->arr[i];
               it.idx = i;
               return it;
           }
       }
      return htab_end(it.t);
   }
   else{
        it.ptr = it.ptr->next;
        return it;
   }
}