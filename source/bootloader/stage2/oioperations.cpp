#include "oioperations.hpp"
#include "x86.hpp"

void cout(char c)
{
    x86_Video_WriteCharTeletype(c, 0);
}
void cout(const char *str)
{
    while (*str)
    {
        cout(*str);
        ++str;
    }
    
}