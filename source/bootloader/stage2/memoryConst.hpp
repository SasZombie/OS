#pragma once


// We know this memory is ocupied
//0x0000000 - 0x000003FF: Interupt VectorTable
//0x0000400 - 0x000004FF: Bios Data Area

#define MEM_MIN 0x00000500;
#define MEM_MAX = 0x00000800;

#define MEMORY_FAT_ADDR ((void far*)0x00500000)    //SEGMENT OFFSET
#define MEMORY_FAT_SIZE 0x00010500

//0x00080000 - 0x0009FFFF - Extended BIOS data area
//0x000A0000 - 0x000C7FFF - Video
//0x000C8000 - 0x000FFFFF - BIOS 