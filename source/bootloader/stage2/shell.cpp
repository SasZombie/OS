#include "shell.hpp"

struct Command
{
    char* name;
    void (*func)(char*** args, Disk &disk);
};

static Disk disk;

//These 2 should always have the same size
static const Command buildins[] = {
    {"clear", clear},
    {"help", help},
    {"ls", ls},
    {"cd", cd},
    {"pwd", pwd}
};

char* currentPath = "/";

const unsigned short nrCom = sizeof(buildins)/sizeof(buildins[0]);

void validateCommand(char* command)
{
    for(unsigned short i = 0; i < nrCom; ++i)
    {
        if(strcmp(command, buildins[i].name) == 0)
        {
            char *sending[2] = {command, currentPath};
            buildins[i].func(&sending, disk);
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