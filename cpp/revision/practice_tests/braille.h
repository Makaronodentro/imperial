#ifndef BRAILLE_H
#define BRAILLE_H

#include <cstring>
#include <cctype>
#include <iostream>
#include <map>

using namespace std;

class Braille {
    private:
        map<const char, const char*> braille;
        
    public:
    
    Braille();
    
    friend int encode_character(const char, char*);
        
    friend void encode(const char*, char*);
    
    friend void print_braille(const char*, ostream*);
};

int encode_character(const char, char*);
    
void encode(const char*, char*);

void print_braille(const char*, ostream&);

#endif