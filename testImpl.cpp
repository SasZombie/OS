#include "testHead.hpp"

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

void pr(float a)
{
    
}