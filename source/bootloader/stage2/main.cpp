#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void*)0)

void dostuff(Disk disk)
{

    FFile f(disk, "/");

    int max = 0;
    while (f.readEntry() && max < 5)
    {
        ++max;
        for (int i = 0; i < 11; i++)
            cout(f.getEntry(i));
        cout("\n");
    }
    f.close();
}

extern "C" {
    void _cdecl cstart_(unsigned short bootDrive)
    {
        // char* dir;
        // cin(dir);
        // // cout(strlen(dir));
        // // if(strcmp(dir, "mydir") == 0)
        // // {
        // //     cout("Da\n");
        // // }
        // Disk disk(bootDrive);
        // FFile f(disk, dir);
        // int max = 0;
        // while (f.readEntry() && max < 5)
        // {
        //     ++max;
        //     for (int i = 0; i < 11; i++)
        //         cout(f.getEntry(i));
        //     cout("\n");
        // }
        // f.close();

        // cout(x86_Create_Dir("MYDAR"));
        // char buffer[100];
        // uint32_t read;
        // f.open("mydir/test.txt");
        // while ((read = f.read(sizeof(buffer), buffer)))
        // {
        //     for (uint32_t i = 0; i < read; i++)
        //     {
        //         cout(buffer[i]);
        //     }
        // }
        // f.close();

        startShell("sas", bootDrive);
        cout("\nEND");
    }
}