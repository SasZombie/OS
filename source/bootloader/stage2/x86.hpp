#pragma once
#include "stdint.hpp"

extern "C"{
    void _cdecl x86_Video_WriteCharTeletype(char c, unsigned char page);
    void _cdecl x86_Read_Character(char *outChar);
    bool _cdecl x86_Create_File(char *fileName);
    bool _cdecl x86_Create_Dir(char *fileName);

    void _cdecl x86_Disk_Write(uint8_t sectors);
    void _cdecl x86_div64_32(unsigned long long int dividend, unsigned long int divisor, unsigned long long int* quotientOut, unsigned long int* remainderOut);
    bool _cdecl x86_Disk_Reset(uint8_t drive);
    bool _cdecl x86_Disk_Read(uint8_t drive, uint8_t cylinder, uint8_t head, uint8_t sector, uint8_t count, void __far *dataOut);
    bool _cdecl x86_Disk_GetDriveParams(uint8_t drive, uint8_t *driveTypeOut, uint16_t* cylinderOut, uint16_t *sectorsOut, uint16_t *headsOut);
}