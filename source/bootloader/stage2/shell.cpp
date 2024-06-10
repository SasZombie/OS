#include "shell.hpp"

struct Command
{
    char* name;
    void (*func)(char* command, char* currentPath, Disk &disk);
};

static Disk disk;

//These 2 should always have the same size
static const Command buildins[] = {
    {"clear", clear},
    {"help", help},
    {"ls", ls},
    {"cd", cd},
    {"pwd", pwd},
    {"cat", cat},
    {"draw face", drawFace},
    {"draw pixels", drawPixels},
    {"draw symbol", drawSymbal}
};

char currentPath[256] = "/";

const unsigned short nrCom = sizeof(buildins)/sizeof(buildins[0]);

void validateCommand(char* command)
{
    for(unsigned short i = 0; i < nrCom; ++i)
    {
        if(strcmp(command, buildins[i].name) == 0)
        {
            buildins[i].func(command, currentPath, disk);
            return;
        }
    }

    cout("Cannot find the command ");
    cout(command);
}

void startShell(const char* name, unsigned short bootDrive)
{
    disk.openDriver(bootDrive);
    
    while (true)
    {
        cout('\n');
        cout(name);
        cout('@');
        cout("sasos > ");
        char* command;
        cin(command);
        validateCommand(command);
    }
    
}