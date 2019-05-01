// # ppm.h
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#ifndef PPM_H
#define PPM_H

#define PPM_SIZE_LIMIT (8000 * 8000 * 3)

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; // RGB bajty -> 3 * xsize * ysize
};

struct ppm * ppm_read(const char *filename);
void ppm_free(struct ppm *p);

#endif