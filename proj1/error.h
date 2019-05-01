// # error.h
// # Řešení IJC-DU1, 20.3.2019
// # Autor: xhajek48 (Karel Hajek), FIT VUT
// # Přeloženo: gcc 8.2.1

#ifndef ERROR_H
#define ERROR_H

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif