// # error.c
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#include <stdarg.h>
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void warning_msg(const char *fmt, ...){
    va_list argPtr;
    va_start(argPtr, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argPtr);
    va_end(argPtr);

}
void error_exit(const char *fmt, ...){
    va_list argPtr;
    va_start(argPtr, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argPtr);
    va_end(argPtr);
    exit(1);
}
