#ifndef PIGLATIN_H
#define PIGLATIN_H

#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

int findFirstVowel(const char*);
    
    bool isVowel(char);

void translateWord(const char*, char*);
    
    void shiftElements(char* in, int n);

void translateStream(istream&, ostream&);

#endif