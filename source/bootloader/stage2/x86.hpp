#pragma once

extern "C"{
    void _cdecl x86_Video_WriteCharTeletype(char c, unsigned char page);
    void _cdecl x86_div64_32(unsigned long long int dividend, unsigned long int divisor, unsigned long long int* quotientOut, unsigned long int* remainderOut);
}