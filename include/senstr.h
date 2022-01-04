#ifndef _SENSTR_H
#define _SENSTR_H 1

#include "sendefs.h"

dynstr sconcatb(dynstr buff, size_t buffN, string val);
dynstr sconcatlimb(dynstr buff, size_t buffN, string val, size_t n);
dynstr sconcatarrd(size_t n, string* arr);
dynstr sconcatarrb(dynstr buff, size_t buffN, size_t n, string* arr);
dynstr sconcatvd(size_t n, ...);
dynstr sconcatvb(dynstr buff, size_t buffN, size_t n, ...);

size_t sfind(string str, string pattern, size_t skipN);
size_t sfindlast(string str, string pattern, size_t skipN);

dynstr sreplaceb(string str, dynstr buff, size_t buffN, string pattern, string val);
dynstr sreplaced(string str, string pattern, string val);

dynstr* ssplitb(dynstr buff1, size_t buff1N, dynstr* buff2, size_t buff2N, string str, string sep, size_t* psize);
dynstr* ssplitd(string str, string sep, size_t* psize);

dynstr sjoinarrb(dynstr buff, size_t buffN, string separator, string* arr, size_t n);
dynstr sjoinarrd(string separator, string* arr, size_t n);

#endif