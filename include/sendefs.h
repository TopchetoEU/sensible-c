#ifndef _SENDEFS_H
#define _SENDEFS_H 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define INDEX_END SIZE_MAX

typedef const char* string;
typedef char* dynstr;

#define sbyte int8_t
#define byte uint8_t
#define ushort uint16_t
#define uint uint32_t
#define ulong uint64_t

#endif