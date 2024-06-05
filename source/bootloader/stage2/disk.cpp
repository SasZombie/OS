#include "disk.hpp"

Disk::Disk()
{
}

void Disk::DISK_LBA2CHS(uint32_t lba, uint16_t* cylinderOut, uint16_t* sectorOut, uint16_t* headOut)
{
    *sectorOut = lba % this->sectors + 1;
    *cylinderOut = (lba / this->sectors) / this->heads;
    *headOut = (lba / this->sectors) % this->heads;
}

Disk::Disk(uint8_t driveNumber)
{
    uint8_t driveType;
    uint16_t cylinders, sectors, heads;

    if (!x86_Disk_GetDriveParams(this->id, &driveType, &cylinders, &sectors, &heads))
    {
        cout("Cannot get Drive Params");
    }

    this->id = driveNumber;
    this->cylinders = cylinders + 1;
    this->heads = heads + 1;
    this->sectors = sectors;
}

void Disk::openDriver(uint8_t driveNumber)
{
    uint8_t driveType;
    uint16_t cylinders, sectors, heads;

    if (!x86_Disk_GetDriveParams(this->id, &driveType, &cylinders, &sectors, &heads))
    {
        cout("Cannot get Drive Params");
    }

    this->id = driveNumber;
    this->cylinders = cylinders + 1;
    this->heads = heads + 1;
    this->sectors = sectors;
}

bool Disk::readSectors(uint32_t lba, uint8_t sectors, void __far *dataOut)
{
    uint16_t cylinder, sector, head;

    DISK_LBA2CHS(lba, &cylinder, &sector, &head);

    for (int i = 0; i < 3; i++)
    {
        if (x86_Disk_Read(this->id, cylinder, sector, head, sectors, dataOut))
            return true;

        x86_Disk_Reset(this->id);
    }

    return false;
}

uint8_t Disk::getOpenedDriver() const
{
    return this->id;
}

uint16_t Disk::getCylinderNumber() const
{
    return this->cylinders;
}

uint16_t Disk::getSectorsNumber() const
{
    return this->sectors;
}

uint16_t Disk::getHeadsNumber() const
{
    return this->heads;
}
