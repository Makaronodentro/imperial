#ifndef CORRECT_H
#define CORRECT_H

#include <iostream>
#include <cstring>

using namespace std;

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);

void text_to_binary(const char*, char*);
void binary_to_text(const char*, char*);

void add_error_correction(const char*, char*);

int decode(char*, char*);

#endif
