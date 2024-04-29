#include "oioperations.hpp"
#include "fat.hpp"
#include "filestream.hpp"
#include "disk.hpp"

#define NULL ((void*)0)

void __far* g_data = (void __far*)0x00500200;

extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        Disk disk(bootDrive);
    
        disk.readSectors(19, 1, g_data);

        // FFile f(disk);

        // f.open("/");

        FFile f(disk, "/");

        int j = 0;
        while(f.readEntry() && j++ < 10)
        {
            cout("  ");
            for (int i = 0; i < 11; i++)
                cout((char) f.getEntry(i));
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
                if (buffer[i] == '\n')
                    cout('\r');
                cout(buffer[i]);
            }
        }
        f.close();

end:
    cout("END");
    for (;;);
    }
}