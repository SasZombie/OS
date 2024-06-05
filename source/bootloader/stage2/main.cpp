#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void*)0)

extern "C" {
    void _cdecl cstart_(unsigned short bootDrive)
    {

        // cout(x86_Create_Dir("MYDAR"));


        Disk disk(bootDrive);


        FFile f(bootDrive, "/");
        int max = 0;
        while (f.readEntry() && max < 5)
        {
            ++max;
            for (int i = 0; i < 11; i++)
                cout(f.getEntry(i));
            cout("\n");
        }
        f.close();


        char buffer[100];
        uint32_t read;
        f.open("mydir/test.txt");
        while ((read = f.read(sizeof(buffer), buffer)))
        {
            for (uint32_t i = 0; i < read; i++)
            {
                cout(buffer[i]);
            }
        }
        f.close();

        startShell("sas");
        cout("\nEND");
    }
}