#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void*)0)

extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        
        // cout(x86_Create_Dir("MYDAR"));

        startShell("sas");

        // Disk disk(bootDrive);

    

        // char buffer[100];
        // uint32_t read;
        // f.open("KERNAL  TXT");
        // while ((read = f.read(sizeof(buffer), buffer)))
        // {
        //     for (uint32_t i = 0; i < read; i++)
        //     {
        //         cout(buffer[i]);
        //     }
        // }
        // f.close();

        cout("\nEND");
    }
}