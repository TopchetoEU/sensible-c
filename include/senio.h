#ifndef _SENIO_H
#define _SENIO_H 1

#include "sendefs.h"
#include <stdio.h>

string sinputd(string question);
string sinputb(string question, dynstr buff, size_t buffN);

string sfinputd(string question, FILE* stream);
string sfinputb(string question, FILE* stream, dynstr buff, size_t buffN);

void _scanf(string format, ...);
void _fscanf(FILE* file, string format, ...);

long sinputnumd(string question);
long sinputnummaxd(string question, long max);
long sinputnummind(string question, long min);
long sinputnumlimd(string question, long min, long max);

float sinputfd(string question);
float sinputfmaxd(string question, float max);
float sinputfmind(string question, float min);
float sinputflimd(string question, float min, float max);

long sinputnumb(string question, dynstr buff, size_t buffN);
long sinputnummaxb(string question, dynstr buff, size_t buffN, long max);
long sinputnumminb(string question, dynstr buff, size_t buffN, long min);
long sinputnumlimb(string question, dynstr buff, size_t buffN, long min, long max);

float sinputfb(string question, dynstr buff, size_t buffN);
float sinputfmaxb(string question, dynstr buff, size_t buffN, float max);
float sinputfminb(string question, dynstr buff, size_t buffN, float min);
float sinputflimb(string question, dynstr buff, size_t buffN, float min, float max);

bool saskyn(string question, bool _default);


#endif