#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void *)0)

extern "C"
{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        cout("Please provide your name: ");
        char name[10];
        cin(name);

        startShell(name, bootDrive);
        cout("\nEND");
    }
}