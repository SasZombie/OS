#include "oioperations.hpp"
#include "fat.hpp"
#include "filestream.hpp"
#include "disk.hpp"

#define NULL ((void*)0)

extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        Disk disk(bootDrive);
        char str[20];

        cin(str);
        cout('\n');
        cout(str);
        cout('\n');

        cout("\nEND");
    }
}