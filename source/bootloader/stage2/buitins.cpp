#include "builtins.hpp"

void clear(char*** args, Disk& disk)
{
    (void)args;

    x86_Clear_Screen();
}

void help(char*** args, Disk& disk)
{
    (void)args;
    cout("Type a command. Commadns are: \n\t help \n\t clear");
}

void ls(char*** args, Disk& disk)
{
    FFile f(disk, *args[1]);
    int max = 0;
    while (f.readEntry() && max < 5)
    {
        ++max;
        for (int i = 0; i < 11; i++)
            cout(f.getEntry(i));
        cout("\n");
    }
    f.close();
}

void cd(char*** args, Disk& disk)
{
    const char* command = *args[0];

    if(strlen(command) == 2)
    {
        *args[1] = "/";
        return;
    }
    // const char* oldPath = args[1];

    char newPath[256];
    unsigned short index = 3;

    while(command[index])
    {
        newPath[index - 3] = command[index];
        ++index;
    }

    FFile f(disk, newPath);

    if(!f.isDirectory())
    {
        cout(newPath);
        cout(" is not a directory!\n");
        f.close();
        return;
    }

    f.close();
    
    *args[1] = "mydir";
    cout(*args[1]);
}

void pwd(char*** args, Disk& disk)
{
    cout(*args[1]);
    cout('\n');
}
