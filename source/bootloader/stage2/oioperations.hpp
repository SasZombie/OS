#pragma once

#define LONG_NUMBERS
// #define FLOAT_NUMBERS
// #define DOUBLE_NUMBERS

void cout(char c);
void cout(char *str);
void cout(const char *str);
void cout(const char __far *str);
void cout(int number);
void cout(short number);
#ifdef FLOAT_NUMBERS
void cout(float number, unsigned short decimals = 6);
#endif 
#ifdef DOUBLE_NUMBERS
void cout(double number, unsigned short decimals = 15);
#endif
void cout(unsigned int number);
void cout(unsigned short number);

//Annoying Error __I4M. Linker tries to link with library, but I dissabled libs
//TODO: Fix the linkage
#ifdef LONG_NUMBERS
void cout(long number);
void cout(long long number);
void cout(unsigned long number);
void cout(unsigned long long number);
#endif
