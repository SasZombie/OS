#include "chartype.hpp"

bool islower(char chr)
{
    return chr >= 'a' && chr <= 'z';
}

char toupper(char chr)
{
    if(chr > 'Z' || chr < 'a')
        return chr;
    return islower(chr) ? (chr + 32) : chr;
}