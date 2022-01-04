#include "sensible.h"
#include <stdio.h>

const short svermaj = 0;
const short svermin = 1;

void sinit(int maj, int min) {
    if (svermaj != maj) {
        printf("An different major version of the library than the header file is used. There may be API mismatches\n");
        return;
    }
    if (svermin < min) {
        printf("An older minor version of the library than the header file is used. Header may describe API that doesn't exist\n");
        return;
    }
}