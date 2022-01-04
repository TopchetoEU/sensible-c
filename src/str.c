#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include "senstr.h"

// To make programming teacher happy
static size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len++]);
    return len - 1;
}

static void tozero(char** pbuff, size_t* pbuffN) {
    while (*(*pbuff)++) (*pbuffN)--;
    (*pbuffN)++;
    (*pbuff)--;
}

// String concatenate buffer
char* sconcatb(char* buff, size_t buffN, const char* val) {
    if (!buffN) return buff;
    tozero(&buff, &buffN);
    if (!buffN) return buff;
    size_t i;

    for (i = 0; val[i] && i < buffN; i++) {
        buff[i] = val[i];
    }

    buff[i] = 0;
    return buff;
}
// String concatenate limited buffer
char* sconcatlimb(char* buff, size_t buffN, const char* val, size_t n) {
    if (!buffN) return buff;
    if (!n) return buff;
    tozero(&buff, &buffN);
    if (!buffN) return buff;
    size_t i;


    for (i = 0; i < n && i < buffN; i++) {
        buff[i] = val[i];
    }

    buff[i] = 0;
    return buff;
}

// String concatenate array dynamic alloc
char* sconcatarrd(size_t n, ...) {
    va_list l;
    va_start(l, n);

    const char** arr = malloc(n * sizeof(const char*));
    size_t len = 0;
    
    for (size_t i = 0; i < n; i++) {
        arr[i] = va_arg(l, const char*);
        len += my_strlen(arr[i]);
    }

    char* res = malloc(len + 1);
    char* tempRes = res;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; arr[i][j]; j++) {
            *(tempRes++) = arr[i][j];
        }
    }

    *tempRes = 0;

    va_end(l);

    return res;
}
// String concatenate array buffer
char* sconcatarrb(char* buff, size_t buffN, size_t n, ...) {
    if (!buffN) return buff;
    if (!n) return buff;
    va_list l;
    va_start(l, n);

    size_t buffI = 0;

    tozero(&buff, &buffN); // Brings the buffer to its first 0
    if (!buffN) return buff;

    for (size_t i = 0; i < n; i++) {
        const char* curr = va_arg(l, const char*);

        for (size_t j = 0; curr[j]; j++) {
            buff[buffI++] = curr[j];
            if (buffI == buffN) {
                // Buffer has ran out :(
                buff[buffI - 1] = 0;
                va_end(l);
                return buff;
            }
        }
    }

    buff[buffI] = 0;

    va_end(l);
    return buff;
}

// String find
long sfind(const char* str, const char* pattern, long skipN) {
    long matchI = 0;

    if (!my_strlen(pattern)) return 0;

    for (long i = skipN; str[i]; i++) {
        if (pattern[matchI++] == str[i]) {
            if (!pattern[matchI]) return i - matchI + 1;
        }
        else matchI = 0;
    }

    return -1;
}
// String find last
long sfindlast(const char* str, const char* pattern, long skipN) {
    long len = my_strlen(str) - 1;
    long patBegin = my_strlen(pattern) - 1;
    long matchI = patBegin;

    if (patBegin + 1 == 0) return len + 1;
    if (len + 1 == 0) return -1;

    for (long i = len; true; i--) {
        if (pattern[matchI] == str[i]) {
            if (matchI == 0) return i;
            matchI--;
        }
        else matchI = patBegin;

        if (!i) return -1;
    }
}

// String replace buffer
char* sreplaceb(const char* str, char* buff, size_t buffN, const char* pattern, const char* val) {
    if (!buffN) return buff;
    if (!my_strlen(pattern)) return buff;

    size_t valLen = my_strlen(val);
    size_t matchI = 0;
    size_t buffI = 0;
    size_t i = 0;

    for (; str[i]; i++) {
        if (pattern[matchI++] == str[i]) {
            if (!pattern[matchI]) {
                sconcatb(buff + buffI, buffN - buffI, val);
                buffI += valLen;
                matchI = 0;
            }
        }
        else {
            sconcatlimb(buff + buffI, buffN - buffI, str + i - matchI + 1, matchI);
            matchI = 0;
        }
    }

    i--;
    sconcatlimb(buff + buffI, buffN - buffI, str + i - matchI + 1, matchI);

    return buff;
}
// String replace dynamic alloc
char* sreplaced(const char* str, const char* pattern, const char* val) {
    size_t allReplaced = my_strlen(str) / my_strlen(pattern) * my_strlen(val) + 1;
    char* buff = malloc(allReplaced);
    sreplaceb(str, buff, allReplaced, pattern, val);
    size_t newLen = my_strlen(buff);
    if (allReplaced != newLen) buff = realloc(buff, newLen + 1);
    return buff;
}

// String split buffer
void ssplitb(char* buff1, size_t buff1N, char** buff2, size_t buff2N, const char* str, const char* sep) {
    char* temp;
    size_t sepLen = my_strlen(sep);

    size_t i = 0;

    while ((i = sfind(str, sep, i)) >= 0) {

    }
}

int main() {
    printf("%ld", sfind("This is a test", "is", 0));
    return 0;
}