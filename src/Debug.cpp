#ifdef DEBUG

#include <iostream>

void Debug(const char *msg) { std::cerr << msg; }
void Debug(const int msg)   { std::cerr << msg; }

#else

void Debug(const char *msg) { }
void Debug(const int msg) { }

#endif
