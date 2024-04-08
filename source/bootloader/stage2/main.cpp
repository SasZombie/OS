#include "oioperations.hpp"
extern "C"{

    void _cdecl cstart_(unsigned short bootDrive)
    {
        (void) bootDrive;
        
        cout("Meow");

    }
}