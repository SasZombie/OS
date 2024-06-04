#pragma once
#include "stdint.hpp"
#include "disk.hpp"
#include "oioperations.hpp"
#include "memoryConst.hpp"
#include "utility.hpp"
#include "cstring.hpp"
#include "memory.hpp"
#include "chartype.hpp"
#include "algorithm.hpp"

#pragma pack(push, 1)

struct FAT_DirectoryEntry
{
    uint8_t Name[11];
    uint8_t Attributes;
    uint8_t _Reserved;
    uint8_t CreatedTimeTenths;
    uint16_t CreatedTime;
    uint16_t CreatedDate;
    uint16_t AccessedDate;
    uint16_t FirstClusterHigh;
    uint16_t ModifiedTime;
    uint16_t ModifiedDate;
    uint16_t FirstClusterLow;
    uint32_t Size;
};

#pragma pack(pop)
//This is FAT16 structure! We need it to be packed, that is, the compiler should not add padding so we have to 
//Use structs

struct FAT_File
{
    int Handle;
    bool IsDirectory;
    uint32_t Position;
    uint32_t Size;
};

//We also are dealing with __fat*. If we use a class this->method() is a near pointer, so the model is going to be near
//We need to use structs with far pointers

enum FAT_Attributes
{
    FAT_ATTRIBUTE_READ_ONLY         = 0x01,
    FAT_ATTRIBUTE_HIDDEN            = 0x02,
    FAT_ATTRIBUTE_SYSTEM            = 0x04,
    FAT_ATTRIBUTE_VOLUME_ID         = 0x08,
    FAT_ATTRIBUTE_DIRECTORY         = 0x10,
    FAT_ATTRIBUTE_ARCHIVE           = 0x20,
    FAT_ATTRIBUTE_LFN               = FAT_ATTRIBUTE_READ_ONLY | FAT_ATTRIBUTE_HIDDEN | FAT_ATTRIBUTE_SYSTEM | FAT_ATTRIBUTE_VOLUME_ID
};

bool FAT_Initialize(Disk & disk);
FAT_File __far* FAT_Open(Disk & disk, const char* path);
uint32_t FAT_Read(Disk & disk, FAT_File __far* file, uint32_t byteCount, void* dataOut);
bool FAT_ReadEntry(Disk & disk, FAT_File __far* file, FAT_DirectoryEntry* dirEntry);
void FAT_Close(FAT_File __far* file);