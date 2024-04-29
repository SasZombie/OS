#include "oioperations.hpp"
#include "fat.hpp"
#include "filestream.hpp"
#include "disk.hpp"

#define NULL ((void*)0)

extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        Disk disk(bootDrive);
        char *str;

        cin(str);
        cout(str);

        cout("\nEND");
    }
}