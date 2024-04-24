#pragma once
#include "stdint.hpp"
#include "x86.hpp"
#include "oioperations.hpp"

class Disk{
private:
    uint8_t id;
    uint16_t cylinders, sectors, heads;
    void Disck_LBA2CHS(uint32_t lba, uint16_t *cylinderOut, uint16_t *sectorsOut, uint16_t* headOut);

public:
    Disk(uint8_t driveNumber);

    bool readSectors(uint32_t lba, uint8_t sectorsToRead, uint8_t __far* dataOut);

    //Getters >_<
    uint8_t getId();
    uint16_t getCylinders();
    uint16_t getSectors();
    uint16_t getHeads();

};
