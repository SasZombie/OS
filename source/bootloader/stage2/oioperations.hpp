#pragma once
#include "x86.hpp"
#include "cstring.hpp"
#include "stdint.hpp"


//Printing
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

//Reading
// cin >> a
//Works by deducing type of a
//We cant do that since I cant include <ctype>

void cin(char &var);
void cin(char *var);

template<typename T>
void cin(T &var)
{
    var = 0;
    char buff[23]; // Max digits read at once!
    char c;
    unsigned index = 0;
    while (c != 0x0D && index != 22)
    {
        cin(c);
        buff[index] = c;
        ++index;
    }
    cout('\n');
    buff[index] = '\0';
    bool isNegative = false;

    if(buff[0] == '-')
        isNegative = true;
        
    unsigned size = strlen(buff);
    for (unsigned int i = isNegative; i < size - 1; ++i)
    {
        var = var * 10 + (T)(buff[i] - '0');
    }

    if(isNegative)
        var = -var;

}