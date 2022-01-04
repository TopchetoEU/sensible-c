#ifndef _SENSIBLE_H
#define _SENSIBLE_H 1

#define SENSIBLE_INIT() (sinit(0, 1))

#include "senconvert.h"
#include "sendefs.h"
#include "senio.h"
#include "senstr.h"

const short svermaj;
const short svermin;

void sinit(int maj, int min);

#endif