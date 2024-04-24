#include "disk.hpp"

Disk::Disk(uint8_t driveNumber)
{
    this->id = driveNumber;
    uint8_t driveType;

    if(!x86_Disk_GetDriveParams(driveNumber, &driveType, &this->cylinders, &this->sectors, &this->heads))
    {
        cout("Disk Get Drive Params failed\n");
    }

}

void Disk::Disck_LBA2CHS(uint32_t lba, uint16_t *cylinderOut, uint16_t *sectorsOut, uint16_t* headOut)  
{
    *sectorsOut = lba % this->sectors + 1;
    *cylinderOut = (lba / this->sectors) / this->heads;
    *headOut = (lba / this->sectors) % this->heads;
}

bool Disk::readSectors(uint32_t lba, uint8_t sectorsToRead, uint8_t __far *dataOut)
{
    uint16_t cylinder, sector, head;
    this->Disck_LBA2CHS(lba, &cylinder, &sector, &head);

    int i = 0;
    do
    {
        ++i;
        if(x86_Disk_Read(this->id, cylinder, sector, head, sectorsToRead, dataOut))
            return true;
        x86_Disk_Reset(this->id);

    } while (i <= 3);

    return false;    
}

uint8_t Disk::getId()  
{
    return this->id;
}

uint16_t Disk::getCylinders()  
{
    return this->cylinders;
}

uint16_t Disk::getSectors()  
{
    return this->sectors;
}

uint16_t Disk::getHeads()  
{
    return this->heads;
}
