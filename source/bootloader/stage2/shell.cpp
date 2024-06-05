#include "shell.hpp"
#include "oioperations.hpp"
#include "cstring.hpp"
#include "builtins.hpp"

struct Command
{
    char* name;
    void (*func)(const char* args);
};


//These 2 should always have the same size
Command buildins[] = {
    {"clear", clear},
    {"help", help}
};

const unsigned short nrCom = sizeof(buildins)/sizeof(buildins[0]);

void validateCommand(const char* command)
{
    for(unsigned short i = 0; i <nrCom; ++i)
    {
        if(strcmp(command, buildins[i].name) == 0)
        {
            buildins[i].func(command);
            return;
        }
    }

    cout("Cannot find the command ");
    cout(command);
}

void startShell(const char* name)
{
    while (true)
    {
        cout('\n');
        cout(name);
        cout('@');
        cout("sasos >");
        char* command;
        cin(command);
        validateCommand(command);
    }
    
}