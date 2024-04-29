#pragma once
#include "fat.hpp"
#include "disk.hpp"


//This is just an encapsulation of the file in fat.hpp
class FFile
{
private:
    Disk &disk;
    FAT_File __far* fd;
    FAT_DirectoryEntry entry;



public:
    FFile(Disk &ndisk);
    FFile(Disk &ndisk, const char *str);

    void open(const char *str);
    bool readEntry();
    void close();
    uint32_t read(uint32_t byteCount, void* dataOut);

    char getEntry(unsigned i);

};