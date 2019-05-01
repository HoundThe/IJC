// # io.h
// # Řešení IJC-DU2, 25.4.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#ifndef _IO_H_
#define _IO_H_

#include <ctype.h> // isspace()
#include <stdio.h> // fprintf()

int get_word(char *s, int max, FILE *f);

#endif 