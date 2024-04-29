#include "filestream.hpp"

FFile::FFile(Disk &ndisk)
    : disk(ndisk)
{
    FAT_Initialize(disk);
}

FFile::FFile(Disk &ndisk, const char *str)
    : disk(ndisk)
{
    FAT_Initialize(disk);
    this->open(str);
}



void FFile::open(const char *str)
{
    this->fd = FAT_Open(disk, str);
}

bool FFile::readEntry()
{
    return FAT_ReadEntry(this->disk, this->fd, &entry);
}

void FFile::close()
{
    FAT_Close(this->fd);
}

uint32_t FFile::read(uint32_t byteCount, void *dataOut)
{
    return FAT_Read(disk, fd, byteCount, dataOut);
}

char FFile::getEntry(unsigned i)
{
    return entry.Name[i];
}
