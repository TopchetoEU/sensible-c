#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <malloc.h>
#include "senstr.h"

// To make programming teacher happy
static void tozero(dynstr* pbuff, size_t* pbuffN) {
    while (*(*pbuff)++) (*pbuffN)--;
    (*pbuffN)++;
    (*pbuff)--;
}

// String concatenate buffer
dynstr sconcatb(dynstr buff, size_t buffN, string val) {
    if (!buffN) return buff;
    tozero(&buff, &buffN);
    if (!buffN) return buff;
    size_t i;

    for (i = 0; i < buffN; i++) {
        buff[i] = val[i];
        if (!val[i]) break;
    }

    buff[i] = 0;
    return buff;
}
// String concatenate limited buffer
dynstr sconcatlimb(dynstr buff, size_t buffN, string val, size_t n) {
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
dynstr sconcatarrd(size_t n, string* arr) {
    size_t len = 0;
    
    for (size_t i = 0; i < n; i++) {
        len += strlen(arr[i]);
    }

    dynstr res = malloc(len + 1);
    dynstr tempRes = res;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; arr[i][j]; j++) {
            *(tempRes++) = arr[i][j];
        }
    }

    *tempRes = 0;

    return res;
}
// String concatenate array buffer
dynstr sconcatarrb(dynstr buff, size_t buffN, size_t n, string* arr) {
    if (!buffN) return buff;
    if (!n) return buff;

    size_t buffI = 0;

    tozero(&buff, &buffN); // Brings the buffer to its first 0
    if (!buffN) return buff;

    for (size_t i = 0; i < n; i++) {
        string curr = arr[i];

        for (size_t j = 0; curr[j]; j++) {
            buff[buffI++] = curr[j];
            if (buffI == buffN) {
                // Buffer has ran out :(
                buff[buffI - 1] = 0;
                return buff;
            }
        }
    }

    buff[buffI] = 0;
    return buff;
}

// String concatenate variadic dynamic alloc
dynstr sconcatvd(size_t n, ...) {
    va_list l;
    va_start(l, n);

    string* arr = malloc(n * sizeof(string));
    
    for (size_t i = 0; i < n; i++) {
        arr[i] = va_arg(l, string);
    }

    return sconcatarrd(n, arr);
}
// String concatenate variadic buffer
dynstr sconcatvb(dynstr buff, size_t buffN, size_t n, ...) {
    if (!buffN) return buff;
    if (!n) return buff;
    va_list l;
    va_start(l, n);

    size_t buffI = 0;

    tozero(&buff, &buffN); // Brings the buffer to its first 0
    if (!buffN) return buff;

    for (size_t i = 0; i < n; i++) {
        string curr = va_arg(l, string);

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
size_t sfind(string str, string pattern, size_t skipN) {
    size_t matchI = 0;

    if (!strlen(pattern)) return 0;

    for (size_t i = skipN; str[i]; i++) {
        if (pattern[matchI++] == str[i]) {
            if (!pattern[matchI]) return i - matchI + 1;
        }
        else matchI = 0;
    }

    return INDEX_END;
}
// String find last
size_t sfindlast(string str, string pattern, size_t skipN) {
    size_t len = strlen(str) - 1;
    size_t patBegin = strlen(pattern) - 1;
    size_t matchI = patBegin;

    if (patBegin + 1 == 0) return len + 1;
    if (len + 1 == 0) return INDEX_END;

    for (size_t i = len; true; i--) {
        if (pattern[matchI] == str[i]) {
            if (matchI == 0) return i;
            matchI--;
        }
        else matchI = patBegin;

        if (!i) return INDEX_END;
    }
}

// String replace buffer
dynstr sreplaceb(string str, dynstr buff, size_t buffN, string pattern, string val) {
    if (!buffN) return buff;
    if (!strlen(pattern)) return buff;

    size_t valLen = strlen(val);
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
dynstr sreplaced(string str, string pattern, string val) {
    size_t allReplaced = strlen(str) / strlen(pattern) * strlen(val) + 1;
    dynstr buff = malloc(allReplaced);
    sreplaceb(str, buff, allReplaced, pattern, val);
    size_t newLen = strlen(buff);
    if (allReplaced != newLen) buff = realloc(buff, newLen + 1);
    return buff;
}

// String split buffer
dynstr* ssplitb(dynstr buff1, size_t buff1N, dynstr* buff2, size_t buff2N, string str, string sep, size_t* psize) {
    if (!buff2N) return NULL;
    if (!buff1N) return NULL;

    size_t sepLen = strlen(sep);

    size_t i = 0;
    size_t size = 0;

    while (*str && (i = sfind(str, sep, 0)) != INDEX_END) {
        if (!sepLen) i++;
        sconcatlimb(buff1, buff1N, str, i);

        if (!buff2N) return buff2;

        *buff2 = buff1;
        buff2++;
        buff2N--;

        str += i + sepLen;
        buff1 += i + 1;
        buff1N -= i + 1;

        size++;
    }

    if (!sepLen) size--;

    if (buff2N) {
        sconcatb(buff1, buff1N, str);
        size++;
        if (!*buff1 && !sepLen) {
            if (psize) *psize = size;
            return buff2;
        }
        *(buff2++) = buff1;
        buff2N++;
    }

    if (buff2N) *buff2 = 0;
    else *(--buff2) = 0;

    if (psize) *psize = size;
    return buff2;
}
// String split dynamic alloc
dynstr* ssplitd(string str, string sep, size_t* psize) {
    size_t buff1N, buff2N;
    dynstr buff1 = malloc(buff1N = strlen(str) * 2 + 2);
    dynstr* buff2 = malloc(sizeof(dynstr*) * (buff2N = strlen(str) + 1));

    *buff2 = 0;
    ssplitb(buff1, buff1N, buff2, buff2N, str, sep, psize);

    return buff2;
}

// string join array buffer
dynstr sjoinarrb(dynstr buff, size_t buffN, string separator, string* arr, size_t n) {
    if (!buffN) return NULL; // empty buffer :(

    size_t sepLen = strlen(separator);

    for (size_t i = 0; i < n; i++) {
        if (i) {
            sconcatb(buff, buffN, separator);
            buff += sepLen;
            buffN -= sepLen;
        }
        sconcatb(buff, buffN, arr[i]);
        tozero(&buff, &buffN);
    }

    return buff;
}
// string join array dynamic alloc
dynstr sjoinarrd(string separator, string* arr, size_t n) {
    size_t sepLen = strlen(separator);
    size_t len = sepLen * (n - 1) + 1;

    for (size_t i = 0; i < n; i++) len += strlen(arr[i]);

    dynstr buff = malloc(len);

    sjoinarrb(buff, len, separator, arr, n);

    return buff;
}
