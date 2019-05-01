// # ppm.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include "ppm.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct ppm * ppm_read(const char *filename){
    FILE *fileHandle;

    if((fileHandle = fopen(filename, "rw")) == NULL){
        warning_msg("Soubor '%s' nelze otevrit.\n", filename);
        return NULL;
    }

    unsigned int xsize;
    unsigned int ysize;
    char fileType[3];
    unsigned char color;

    if(fscanf(fileHandle, "%2s %u %u %hhu", fileType, &xsize, &ysize, &color) < 4 ){
        warning_msg("Neslo nacist hlavicku souboru '%s'.\n", filename);
        fclose(fileHandle);
        return NULL;
    }

    if(strcmp(fileType, "P6")) {
        warning_msg("Spatny format souboru: '%s'.\n", filename);
        fclose(fileHandle);
        return NULL;
    }
    size_t ppmDataSize = (3* xsize * ysize);

    if(ppmDataSize > PPM_SIZE_LIMIT){
        warning_msg("Obrazek je prilis velky.\n");
        fclose(fileHandle);
        return NULL;
    }
    struct ppm *ppm_ptr = malloc(sizeof(struct ppm) + ppmDataSize);
    if (ppm_ptr == NULL) {
        warning_msg("Alokace selhala.\n");
        fclose(fileHandle);
        return NULL;
    }
    ppm_ptr->xsize=xsize;
    ppm_ptr->ysize=ysize;

    if(fread(ppm_ptr->data, sizeof(char), ppmDataSize, fileHandle) != ppmDataSize){
        warning_msg("Nepodarilo se nacist data ze souboru: '%s'.\n", filename);
        fclose(fileHandle);
        free(ppm_ptr);
        return NULL;
    }

    fclose(fileHandle);
    return ppm_ptr;
}
void ppm_free(struct ppm *p){
    free(p);
}