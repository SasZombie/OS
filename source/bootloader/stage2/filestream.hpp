#pragma once
#include "fat.hpp"
#include "disk.hpp"


//This is just an encapsulation of the file in fat.hpp
class FFile
{
private:
    bool isOpned;
    const char* currentPath;
    Disk &disk;
    FAT_File __far* fd;
    FAT_DirectoryEntry entry;



public:
    FFile(Disk &ndisk);
    FFile(Disk &ndisk, const char *str);

    void open(const char *str);
    bool readEntry();
    bool isDirectory() const;
    void close();
    uint32_t read(uint32_t byteCount, void* dataOut);
    

    uint32_t fileSize() const;
    const char* getCurrentPath();
    char getEntry(unsigned i);
};
//Example of how to use cuz I always forget
//       FFile f(bootDrive, "/");
// int max = 0;
// while (f.readEntry() && max < 5)
// {
//     for (int i = 0; i < 11; i++)
//         cout(entry.Name[i]);
//     cout("\n");
// }
//     f.close

// 
//     char buffer[100];
//     uint32_t read;
//     f.open("mydir/test.txt");
//     while ((read = f.read(sizeof(buffer), buffer)))
//     {
//         for (uint32_t i = 0; i < read; i++)
//         {
//             cout(buffer[i]);
//         }
//     }
//     f.close()