#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <cstring>

using namespace std;

int substring_position(const char*, const char*);

bool is_prefix(const char*, const char*);

int substring_position2(const char*, const char*, const char* t = 0);
#endif