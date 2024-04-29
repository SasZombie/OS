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

// template<typename T>
// void cin(T *var)
// {
//     char buff[100]; //Max chars read at once!
//     char c;
//     unsigned index = 0;
//     while (c != 0x0D && index != 99)
//     {
//         x86_Read_Character(& c);
//         buff[index] = c;
//         ++index;
//     }

//     buff[index] = '\0';

//     *var = buff;    
// }

void cin(char &var)
{
    x86_Read_Character(&var);
    cout(var);
}

void cin(char *var)
{
    char buff[100]; //Max chars read at once!
    char c;
    unsigned index = 0;
    while (c != 0x0D && index != 99)
    {
        cin(c);
        buff[index] = c;
        ++index;
    }

    
    buff[index] = '\0';

    unsigned size = strlen(buff);
    for(unsigned int i = 0; i < size; ++i)
    {
        // if(var[i] == '\0')
            // break;
        var[i] = buff[i];
    }
    

}