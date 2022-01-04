#ifndef _SENCONVERT_H
#define _SENCONVERT_H 1

#include "sendefs.h"

bool sstrtos(string str, short* resd);
bool sstrtoxs(string str, ushort* resd);
bool sstrtous(string str, ushort* resd);

bool sstrtoi(string str, int* resd);
bool sstrtoxi(string str, uint* resd);
bool sstrtoui(string str, uint* resd);

bool sstrtol(string str, long* presd);
bool sstrtoxl(string str, ulong* presd);
bool sstrtoul(string str, ulong* presd);

bool sstrtof(string str, float* resd);
bool sstrtod(string str, double* resd);

#endif