// # io.c
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "io.h"

int get_word(char *s, int max, FILE *f){

    if(!f){
        fprintf(stderr, "File is NULL\n");
        return -1;
    }
    int foo = 0; // int for EOF

    while ((foo=fgetc(f)) != EOF && isspace(foo)) ;

    if(foo == EOF) return EOF; 

    s[0] = foo;
    int i = 1;
    for(    ; i < max - 1; ){
        foo = fgetc(f);
        if((isspace(foo)) || (foo == EOF)) break;
        s[i]=foo; 
        i++;
    }
    s[i]='\0'; // Terminate your strings kids
    
    if(i == max-1){ // Word was too long for the first time
       // Skip rest of the word
       while((foo = fgetc(f)) != EOF){
           if(isspace(foo)) break;
           i++;
       }
    }
    return i;
}