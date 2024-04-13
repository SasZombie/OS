#include "testHead.hpp"
#include <numeric>
#include <typeinfo>
#include <type_traits>

void pr(char c)
{
    putchar(c);
}

void pr(const char *str)
{
    while (*str)
    {
        pr(*str);
        ++str;
    }
}

void pr(char *str)
{
    while (*str)
    {
        pr(*str);
        ++str;
    }
}

#define FLOAT_NUMBERS

void pr(float number, unsigned int decimals)
{

#ifdef FLOAT_NUMBERS
    char numbers[] = "0123456789";
    char buffer[40];
    short i = 0;
    if(number < 0)
    {
        pr('-');
        number = number * -1;
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
    pr(buffer);
#else
    (void)number;
    (void)decimals;
#endif   

}