#include "oioperations.hpp"
#include "fat.hpp"
#include "disk.hpp"

#define NULL ((void*)0)

void __far* g_data = (void __far*)0x00500200;

extern "C"{
    void _cdecl cstart_(unsigned short bootDrive)
    {
        DISK disk;
        if (!DISK_Initialize(&disk, bootDrive))
        {
            cout("Disk init error\r\n");
            goto end;
        }

        DISK_ReadSectors(&disk, 19, 1, g_data);

        if (!FAT_Initialize(&disk))
        {
            cout("FAT init error\r\n");
            goto end;
        }

    // // browse files in root
    FAT_File far* fd = FAT_Open(&disk, "/");
    FAT_DirectoryEntry entry;
    int i = 0;
    while (FAT_ReadEntry(&disk, fd, &entry) && i++ < 10)
    {
        cout("  ");
        for (int i = 0; i < 11; i++)
            cout((char)entry.Name[i]);
        cout("\n");
    }
    FAT_Close(fd);


    char buffer[100];
    uint32_t read;
    fd = FAT_Open(&disk, "mydir/test.txt");
    while ((read = FAT_Read(&disk, fd, sizeof(buffer), buffer)))
    {
        for (uint32_t i = 0; i < read; i++)
        {
            if (buffer[i] == '\n')
                cout('\r');
            cout(buffer[i]);
        }
    }
    FAT_Close(fd);

end:
    cout("END");
    for (;;);
    }
}