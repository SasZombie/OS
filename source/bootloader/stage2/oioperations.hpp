#pragma once

void cout(char c);
void cout(char *str);
void cout(const char *str);
void cout(const char __far *str);
void cout(int number);
void cout(short number);
void cout(float number);
void cout(double number);
void cout(unsigned int number);
void cout(unsigned short number);

//Annoying Error __I4M. Linker tries to link with library, but I dissabled libs
//TODO: Fix the linkage
#if LONG_NUMBERS
void cout(long number);
void cout(long long number);
void cout(unsigned long number);
void cout(unsigned long long number);
#endif
