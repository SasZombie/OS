#pragma once
#include <iostream>

static char numbers[] = "0123456789";

void pr(char a);
void pr(char* a);
void pr(const char* a);


template<typename T>
void pr(T number)
{
    char buffer[20];
    short i = 0;
    int negative = 1;
    if(number < 0)
    {
        pr('-');
        negative = -1;
    }   
    
    number = number * negative;

    while(number)
    {
        buffer[i] = numbers[number%10];
        ++i;
        number = number/10;
    }
    --i;
    while(i >= 0)
    {
        pr(static_cast<char>(buffer[i]));    
        --i;
    }
}