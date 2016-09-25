#ifndef DEBUG_H
#define DEBUG_H

#ifdef UNIT_TEST

#include <iostream>

void Debug(const char *msg) { std::cerr << msg; }
void Debug(const int msg)   { std::cerr << msg; }

#else

void Debug(const char *msg) { }
void Debug(const int msg) { }

#endif  // UNIT_TEST
#endif  // DEBUG_H
