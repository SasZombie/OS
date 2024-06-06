#include "builtins.hpp"

void clear(char* command, char* currentPath, Disk& disk)
{
    x86_Clear_Screen();
}

void help(char* command, char* currentPath, Disk& disk)
{
    cout("Type a command. Commadns are: \n\t help \n\t clear \n\t ls \n\t pwd \n\t cd \n\t cat");
}

void ls(char* command, char* currentPath, Disk& disk)
{
    // cout("Hello");
    cout(currentPath);
    FFile f(disk);

    char dir[] = "mydir";
    char folder[] = "/";

    if(strcmp(currentPath, "mydir") == 0)
    {
        f.open(dir);
    }
    else
    {
        f.open(folder);
    }

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

void cd(char* command, char* currentPath, Disk& disk)
{

    if (strlen(command) == 2)
    {
        strcpy(currentPath, "/");
        cout(currentPath);
        return;
    }
    // const char* oldPath = args[1];

    char newPath[256];
    unsigned short index = 3;

    while (command[index])
    {
        newPath[index - 3] = command[index];
        ++index;
    }

    FFile f(disk, newPath);

    if (!f.isDirectory())
    {
        cout(newPath);
        cout(" is not a directory!\n");
        f.close();
        return;
    }

    f.close();

    strcpy(currentPath, "mydir");
    if(strcmp(currentPath, "mydir") == 0)
    {
        cout("DA");
    }
    // cout(*currentPath);
}

void pwd(char* command, char* currentPath, Disk& disk)
{
    cout(currentPath);
}

void cat(char* command, char* currentPath, Disk& disk)
{
    FFile f(disk, command + 4);

    char buffer[100];
    uint32_t read;
    while ((read = f.read(sizeof(buffer), buffer)))
    {
        for (uint32_t i = 0; i < read; i++)
        {
            cout(buffer[i]);
        }
    }
    f.close();
}