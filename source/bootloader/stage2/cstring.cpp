#include "cstring.hpp"

const char* strchr(const char *str, char chr)
{
    if(str == '\0')
        return '\0';

    while (*str)
    {
        if(*str == chr)
            return str;
        ++str;
    }

    return '\0';
}

void strcpy(char *dest, const char *from)
{
    if(from == '\0')
        return;

    while (*from)
    {
        *dest = *from;
        ++from;
        ++dest;
    }
    *dest = '\0';
}

unsigned int strlen(const char *str)
{
    unsigned int len = 0;

    while (*str)
    {
        ++str;
        ++len;
    }
    
    return len;
}

int strcmp(const char* first, const char* seccond)
{
    while (*first && *seccond)
    {
        if(*first > *seccond)
        {
            return -1;
        }
        else if(*first < *seccond)
        {
            return 1;
        }

        ++first;
        ++seccond;
    }

    return 0;
    
}