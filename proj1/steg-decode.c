// # steg-decode.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "error.h"
#include "ppm.h"
#include "eratosthenes.h"
#include <stdio.h>

const char usage[] = "usage: ./steg-decode <ppm-filename>";

int main(int argc, char **argv){

    if(argc != 2) error_exit("Spatne argumenty, %s\n", usage);

    struct ppm *ppm_ptr = ppm_read(argv[1]);
    if(ppm_ptr == NULL)  error_exit("Nepodarilo se nacist obrazek: '%s'.\n", argv[1]);

    unsigned dataSize = (ppm_ptr->xsize * ppm_ptr->ysize * 3);
    bit_array_alloc(primes, dataSize);
    
    Eratosthenes(primes);

    char messageByte[] = {0};
    size_t j = 0;

    char *bytes = ppm_ptr->data;

    for(size_t i = 19; i < dataSize; i++){
        if(bit_array_getbit(primes, i) != 0) continue; // skipping non-primes
        setbit(messageByte, j, getbit((&(bytes[i+1])), 0));
        j++;
        if(j >= 8){
            if(messageByte[0] == '\0'){
                putchar('\n');
                bit_array_free(primes);
                ppm_free(ppm_ptr);
                return EXIT_SUCCESS;
            }
            putchar(messageByte[0]);
            j = 0;
            *messageByte = 0;
        }        
    }

    ppm_free(ppm_ptr);
    bit_array_free(primes);
    error_exit("Nenalezen konec zpravy.\n");
}