#ifndef WORDS_H
#define WORDS_H

#include <cstring>
#include <iostream>
#include <cctype>

using namespace std;

void reverse(const char*, char*);

bool compare(const char*, const char*);

bool palindrome(const char*);

bool anagram(const char*, const char*);

#endif