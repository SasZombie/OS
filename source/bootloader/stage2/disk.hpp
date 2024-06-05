#pragma once

#include "stdint.hpp"
#include "x86.hpp"
#include "oioperations.hpp"

class Disk
{
private:
    uint8_t id;
    uint16_t cylinders;
    uint16_t sectors;
    uint16_t heads;

    void DISK_LBA2CHS(uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut);

public:

    Disk();
    Disk(uint8_t driveNumber);
    void openDriver(uint8_t driveNumber);
    bool readSectors(uint32_t lba, uint8_t sectors, void __far* dataOut);

    uint8_t getOpenedDriver() const;
    uint16_t getCylinderNumber() const;
    uint16_t getSectorsNumber() const;
    uint16_t getHeadsNumber() const;

};