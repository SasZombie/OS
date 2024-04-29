#pragma once
#include "oioperations.hpp"

#define __I4M


void cout(char c)
{
    if(c == '\n')
        x86_Video_WriteCharTeletype('\r', 0);

    x86_Video_WriteCharTeletype(c, 0);

}

void cout(const char __far *str)
{
    while(*str)
    {
        cout(*str);
        ++str;
    }
}

void cout(const char *str)
{
    while (*str)
    {
        cout(*str);
        ++str;
    }
}
void cout(char *str)
{
    while (*str)
    {
        cout(*str);
        ++str;
    }
}

template<typename T>
static inline void printSinged(T number)
{

    char numbers[] = "0123456789";
    char buffer[20];
    short i = 0;
    int negative = 1;
    if(number < 0)
    {
        cout('-');
        number = -number;
    }   
    //Compiler casts to the biggest type possible! But at the same time in 16 bit real mode, it doesnt know how to divide a 64 number 
    //By another 64 number. 
    //Normal / and % would create problems if number is big
    //And long, long long wouldnt even compile since it calls to external lib
    unsigned long radix = 10;
    unsigned long long divident = static_cast<unsigned long long>(number);

    do
    {
        uint32_t rem;
        x86_div64_32(divident, radix, &divident, &rem);
        buffer[i++] = numbers[rem];
    }while(divident);

    --i;
    while(i >= 0)
    {
        cout(static_cast<char>(buffer[i]));    
        --i;
    }
}


template<typename T>
static inline void printUnsinged(T number)
{
    char numbers[] = "0123456789";
    char buffer[20];
    short i = 0; 

    //Compiler casts to the biggest type possible! But at the same time in 16 bit real mode, it doesnt know how to divide a 64 number 
    //By another 64 number. 
    //Normal / and % would create problems if number is big
    //And long, long long wouldnt even compile since it calls to external lib
    unsigned long radix = 10;
    unsigned long long divident = static_cast<unsigned long long>(number);
    
    do
    {
        uint32_t rem;
        x86_div64_32(divident, radix, &divident, &rem);
        buffer[i++] = numbers[rem];
    }while(divident);

    --i;
    while(i >= 0)
    {
        cout(static_cast<char>(buffer[i]));    
        --i;
    }
}

void cout(int number)
{
    printSinged(number);
}

void cout(short number)
{
    printSinged(number);
}

void cout(float number, unsigned short decimals)
{

#ifdef FLOAT_NUMBERS
    char numbers[] = "0123456789";
    char buffer[40];
    short i = 0;
    if(number < 0)
    {
        cout('-');
        number = -number;
    }   

    unsigned int integerPart = static_cast<int>(number);
    float frac_part = number - integerPart;

    do
    {
        int digit = integerPart % 10;
        buffer[i++] = numbers[digit];
        integerPart = integerPart / 10;

    }while(integerPart);


    buffer[i++] = '.';

    for (int j = 0; j < decimals; j++)
    { 
        frac_part *= 10;
        int digit = static_cast<int>(frac_part);
        buffer[i++] = numbers[digit];
        frac_part = frac_part - digit;
    }
    buffer[i] = '\0';
    cout(buffer);
#else
    (void)number;
    (void)decimals;
#endif   
}

void cout(double number, int decimals)
{


#ifdef DOUBLE_NUMBERS
    char numbers[] = "0123456789";
    char buffer[40];
    short i = 0;
    if(number < 0)
    {
        cout('-');
        number = -number;
    }   

    unsigned int integerPart = static_cast<int>(number);
    double frac_part = number - integerPart;

    do
    {
        int digit = integerPart % 10;
        buffer[i++] = numbers[digit];
        integerPart = integerPart / 10;

    }while(integerPart);


    buffer[i++] = '.';

    for (int j = 0; j < decimals; j++)
    { 
        frac_part *= 10;
        int digit = static_cast<int>(frac_part);
        buffer[i++] = numbers[digit];
        frac_part = frac_part - digit;
    }
    buffer[i] = '\0';
    cout(buffer);
#else
    (void)number;
    (void)decimals;
#endif   
}

void cout(unsigned int number)
{
    printUnsinged(number);   
}

void cout(unsigned short number)
{
    printUnsinged(number);
}

#ifdef LONG_NUMBERS
void cout(long number)
{
    printSinged(number);
}

void cout(long long number)
{
    printSinged(number);
}

void cout(unsigned long number)
{
    printUnsinged(number);
}

void cout(unsigned long long number)
{
    printUnsinged(number);
}
#endif