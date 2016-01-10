#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

void encode(const char*, char*);

    // Auxiliaries for encode
    bool skip(char c);
    char getCode(char c);

bool compare(const char*, const char*);

int count(const char*, const char*);

#endif