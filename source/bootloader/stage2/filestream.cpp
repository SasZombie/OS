#include "filestream.hpp"

FFile::FFile(Disk &ndisk)
    : disk(ndisk)
{
    this->isOpned = false;
    FAT_Initialize(disk);
}

FFile::FFile(Disk &ndisk, const char *str)
    : disk(ndisk)
{
    this->isOpned = true;
    FAT_Initialize(disk);
    this->open(str);
}

void FFile::open(const char *str)
{
    if(this->isOpned)   //Guard
    {
        this->close();
    }
    this->isOpned = true;
    this->fd = FAT_Open(disk, str);
}

bool FFile::readEntry()
{
    return FAT_ReadEntry(this->disk, this->fd, &entry);
}

bool FFile::isDirectory() const
{
    return this->fd->IsDirectory;
}

void FFile::close()
{
    this->isOpned = false;
    FAT_Close(this->fd);
}

uint32_t FFile::read(uint32_t byteCount, void *dataOut)
{
    return FAT_Read(disk, fd, byteCount, dataOut);
}

const char* FFile::getCurrentPath()
{
    return currentPath;
}

char FFile::getEntry(unsigned i)
{
    return entry.Name[i];
}
