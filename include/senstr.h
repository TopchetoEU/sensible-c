#ifndef _SENSTR_H
#define _SENSTR_H 1

#include <stdint.h>
#include <stdbool.h>

char* sconcatb(char* buff, size_t buffN, const char* val);
char* sconcatlimb(char* buff, size_t buffN, const char* val, size_t n);

char* sconcatarrd(size_t n, ...);
char* sconcatarrb(char* buff, size_t buffN, size_t n, ...);

char* sreplaceb(const char* str, char* buff, size_t buffN, const char* pattern, const char* val);
char* sreplaced(const char* str, const char* pattern, const char* val);

long sfind(const char* str, const char* pattern, long start);
long sfindlast(const char* str, const char* pattern, long skipN);

#endif