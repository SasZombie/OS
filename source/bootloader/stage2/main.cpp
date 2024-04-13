#include "oioperations.hpp"


extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        (void) bootDrive;
        cout("Hello world from C!\r\n");
        int a = 32;
        long a2 = 45;
        cout(a2);

        
    }
}