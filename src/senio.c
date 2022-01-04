#include "senio.h"
#include "senconvert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

string sinputd(string question) {
    return sfinputd(question, stdin);
}
string sinputb(string question, dynstr buff, size_t buffN) {
    return sfinputb(question, stdin, buff, buffN);
}

string sfinputd(string question, FILE* stream) {
    size_t cap = 32, n = 0;
    dynstr buff = malloc(cap);
    int c;

    if (question) fputs(question, stdout);

    while ((c = fgetc(stream)) != '\n') {
        if (cap == n) buff = realloc(buff, cap <<= 1);
        buff[n++] = c;
    }

    buff = realloc(buff, n + 1);
    buff[n] = 0;

    return buff;
}
string sfinputb(string question, FILE* stream, dynstr buff, size_t buffN) {
    size_t n = 0;
    int c;

    if (question) fputs(question, stdout);

    if (buffN == 0) return NULL;

    while ((c = fgetc(stream)) != '\n') {
        if (n == buffN - 1) break;
        buff[n++] = c;
    }

    buff[n] = 0;

    return buff;
}

void _scanf(string format, ...) {
    string inp = sinputd(NULL);

    va_list l;
    va_start(l, format);

    vsscanf(inp, format, l);
    free(inp);

    va_end(l);
}
void _fscanf(FILE* file, string format, ...) {
    string inp = sfinputd(NULL, file);

    va_list l;
    va_start(l, format);

    vsscanf(inp, format, l);
    free(inp);

    va_end(l);
}

long sinputnumd(string question) {
    string inp = 0;
    long res;

    do {
        if (inp) free(inp);
        inp = sinputd(question);
    } while (!sstrtol(inp, &res));

    return res;
}
long sinputnummaxd(string question, long max) {
    long res;

    do {
        res = sinputnumd(question);
    } while (res > max);

    return res;
}
long sinputnummind(string question, long min) {
    long res;

    do {
        res = sinputnumd(question);
    } while (res < min);

    return res;
}
long sinputnumlimd(string question, long min, long max) {
    long res;

    do {
        res = sinputnumd(question);
    } while (res < min || res > max);

    return res;
}

float sinputfd(string question) {
    string inp = 0;
    float res;

    do {
        if (inp) free(inp);
        inp = sinputd(question);
    } while (!sstrtof(inp, &res));

    return res;
}
float sinputfmaxd(string question, float max) {
    float res;

    do {
        res = sinputfd(question);
    } while (res > max);

    return res;
}
float sinputfmind(string question, float min) {
    float res;

    do {
        res = sinputfd(question);
    } while (res < min);

    return res;
}
float sinputflimd(string question, float min, float max) {
    float res;

    do {
        res = sinputfd(question);
    } while (res < min || res > max);

    return res;
}

long sinputnumb(string question, dynstr buff, size_t buffN) {
    long res;

    do {
        sinputb(question, buff, buffN);
    } while (sstrtol(buff, &res));

    return res;
}

long sinputnummaxb(string question, dynstr buff, size_t buffN, long max)  {
    float res;

    do {
        res = sinputnumb(question, buff, buffN);
    } while (res > max);

    return res;
}
long sinputnumminb(string question, dynstr buff, size_t buffN, long min) {
    float res;

    do {
        res = sinputnumb(question, buff, buffN);
    } while (res < min);

    return res;
}
long sinputnumlimb(string question, dynstr buff, size_t buffN, long min, long max) {
    float res;

    do {
        res = sinputnumb(question, buff, buffN);
    } while (res > max || res < min);    return res;    return res;

    return res;
}


float sinputfb(string question, dynstr buff, size_t buffN) {
    float res;

    do {
        sinputb(question, buff, buffN);
    } while (sstrtof(buff, &res));

    return res;
}

float sinputfmaxb(string question, dynstr buff, size_t buffN, float max) {
    float res;

    do {
        res = sinputfb(question, buff, buffN);
    } while (res > max);

    return res;
}
float sinputfminb(string question, dynstr buff, size_t buffN, float min) {
    float res;

    do {
        res = sinputfb(question, buff, buffN);
    } while (res < min);
    
    return res;
}
float sinputflimb(string question, dynstr buff, size_t buffN, float min, float max) {
    float res;

    do {
        res = sinputfb(question, buff, buffN);
    } while (res > max || res < min);
    
    return res;
}


bool saskyn(string question,  bool _default);