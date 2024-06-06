#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void*)0)

extern "C" {
    void _cdecl cstart_(unsigned short bootDrive)
    {
        startShell("sas", bootDrive);
        cout("\nEND");
    }
}