/**
 * @file wordcount.c
 * @author Karel Hajek 
 * @login xhajek48 (VUT FIT)
 * @version 0.1
 * @date 2019-04-03
 * 
 * Compiled with: gcc -std=c99 -pedantic -Wall -Wextra
 */

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

// Maximalni delka slova
#define MAX_WORD_LENGTH 128

// Velikost pole jsem vybral podle prumerneho poctu unikatnich slov
// z 20 knih, a tak aby bylo prvocislo (kvuli lepsim vysledkum pri deleni)
#define HTAB_SIZE 20763

int main(void)
{   
    FILE *f = stdin;
    
    char *s = malloc(MAX_WORD_LENGTH);
    if(!s){
        fprintf(stderr, "Allocation failed.\n");
        return 1;
    }
    htab_t *map = htab_init(HTAB_SIZE);
    if(!map){
        fprintf(stderr, "Allocation failed.\n");
        return 1;
    }
    unsigned char wasTruncated = 0;
    int wordLength = 0;
    
    while((wordLength = get_word(s, MAX_WORD_LENGTH, f)) != EOF){
        // Checking if word was too long
        if(wordLength >= MAX_WORD_LENGTH && !wasTruncated){
            fprintf(stderr, "Error: Word was too long (over %d letters) and has been truncated\n", MAX_WORD_LENGTH-1);
            wasTruncated = 1;
        }
        htab_iterator_t foo = htab_lookup_add(map, s);
        // testing if all items are successfuly added
        if(!htab_iterator_valid(foo)){
            fprintf(stderr, "Error occured while inserting items\n");
            htab_free(map);
            free(s);
            return 1;
        }
        // increment number of occurences
        htab_iterator_set_value(foo, htab_iterator_get_value(foo)+1);
    }

    htab_iterator_t end = htab_end(map);
    for(htab_iterator_t i= htab_begin(map); !htab_iterator_equal(i, end); i = htab_iterator_next(i)) {
        printf("%s\t%d\n", htab_iterator_get_key(i), htab_iterator_get_value(i));
    }

    #ifdef TEST // Testing htab_move function
        htab_t *newMap = htab_move(5000, map);
        end = htab_end(newMap);
        for(htab_iterator_t i= htab_begin(newMap); !htab_iterator_equal(i, end); i =    htab_iterator_next(i)) {
            printf("TEST: %s\t%d\n", htab_iterator_get_key(i),  htab_iterator_get_value(i));
        }
        htab_free(newMap);
    #endif
    
    htab_free(map);
    free(s);
    return 0;
}
