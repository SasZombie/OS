#pragma once
#include "oioperations.hpp"
#include "x86.hpp"
#include "stdint.hpp"

void cout(char c)
{
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
inline void printSinged(T number)
{

    char numbers[] = "0123456789";
    char buffer[20];
    short i = 0;
    int negative = 1;
    if(number < 0)
    {
        cout('-');
        negative = -1;
    }   
    
    number = number * negative;


    do
    {
        buffer[i] = numbers[number%10];
        ++i;
        number = number/10;

    }while(number);

    --i;
    while(i >= 0)
    {
        cout(static_cast<char>(buffer[i]));    
        --i;
    }
}


template<typename T>
inline void printUnsinged(T number)
{
    char numbers[] = "0123456789";
    char buffer[20];
    short i = 0; 

    do
    {
        buffer[i] = numbers[number%10];
        ++i;
        number = number/10;
    }while(number);

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

void cout(float number)
{
    (void) number;
}

void cout(double number)
{
    (void) number;
}

void cout(unsigned int number)
{
    printUnsinged(number);   
}

void cout(unsigned short number)
{
    printUnsinged(number);
}

// void cout(long number)
// {
//     printSinged(number);
// }

// void cout(long long number)
// {
//     printSinged(number);
// }

// void cout(unsigned long number)
// {
//     printUnsinged(number);
// }

// void cout(unsigned long long number)
// {
//     printUnsinged(number);
// }
