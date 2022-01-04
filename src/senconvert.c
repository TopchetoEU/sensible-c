#include "senconvert.h"

static bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

bool sstrtos(string str, short* res) {
    long lres;
    if (!sstrtol(str, &lres)) return false;
    *res = lres;
    return true;
}
bool sstrtoxs(string str, ushort* res) {
    ulong lres;
    if (!sstrtoxl(str, &lres)) return false;
    *res = lres;
    return true;
}
bool sstrtous(string str, ushort* res) {
    ulong lres;
    if (!sstrtoul(str, &lres)) return false;
    *res = lres;
    return true;
}

bool sstrtoi(string str, int* res) {
    long lres;
    if (!sstrtol(str, &lres)) return false;
    *res = lres;
    return true;
}
bool sstrtoxi(string str, uint* res) {
    ulong lres;
    if (!sstrtoxl(str, &lres)) return false;
    *res = lres;
    return true;
}
bool sstrtoui(string str, uint* res) {
    ulong lres;
    if (!sstrtoul(str, &lres)) return false;
    *res = lres;
    return true;
}

bool sstrtol(string str, long* pres) {
    long res = 0;
    bool negative = false;

    if (*str == '-') {
        negative = true;
        str++;
        while (isSpace(*(str))) str++;
        if (!*str) return false;
    }

    for (size_t i = 0; str[i]; i++) {
        res *= 10;
        uint digit = str[i] - '0';

        if (digit > 9) {
            if (isSpace(str[i])) break;
            return false;
        }

        res += digit;
    }

    *pres = negative ? -res : res;
    return true;
}
bool sstrtoxl(string str, ulong* pres) {
    ulong res = 0;

    for (size_t i = 0; str[i]; i++) {
        res <<= 4;
        uint digit = str[i];

        if (digit >= '0' && digit <= '9') digit -= '0';
        else if (digit >= 'A' && digit <= 'F') digit = digit - 'A' + 10;
        else if (digit >= 'a' && digit <= 'f') digit = digit - 'a' + 10;
        else if (isSpace(str[i])) break;
        else return false;

        res |= digit;
    }

    *pres = res;
    return true;
}
bool sstrtoul(string str, ulong* pres) {
    ulong res = 0;

    for (size_t i = 0; str[i]; i++) {
        res *= 10;
        uint digit = str[i] - '0';

        if (digit > 9) {
            if (isSpace(str[i])) break;
            return false;
        }

        res += digit;
    }

    *pres = res;
    return true;
}

bool sstrtof(string str, float* res) {
    double dres;
    if (!sstrtod(str, &dres)) return false;
    *res = dres;
    return true;
}
bool sstrtod(string str, double* pres) {
    double whole = 0, part = 0;
    size_t partDigits = 0;
    bool negative = false, parsingPart = false;

    if (*str == '-') {
        negative = true;
        str++;
        while (isSpace(*(str))) str++;
        if (!*str) return false;
    }

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == '.') {
            if (parsingPart) return false;
            parsingPart = true;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            if (parsingPart) {
                part *= 10;
                part += str[i] - '0';
                partDigits++;
            }
            else {
                whole *= 10;
                whole += str[i] - '0';
            }
        }
        else if (isSpace(str[i])) break;
        else return false;
    }

    for (size_t i = 0; i < partDigits; i++) {
        part /= 10;
    }

    whole += part;

    *pres = negative ? -whole : whole;
    return true;
}
