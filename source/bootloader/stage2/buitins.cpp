#include "builtins.hpp"

void clear(char* command, char* currentPath, Disk& disk)
{
    x86_Clear_Screen();
}

void help(char* command, char* currentPath, Disk& disk)
{
    cout("Type a command. Commadns are: \n\t help \n\t clear \n\t ls \n\t pwd \n\t cd \n\t cat \n\t draw face");
}

void ls(char* command, char* currentPath, Disk& disk)
{

    cout(currentPath);
    FFile f(disk);

    char dir[] = "mydir";
    char folder[] = "/";

    if (strcmp(currentPath, "mydir") == 0)
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
    if (strcmp(currentPath, "mydir") == 0)
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
struct Point
{
    int16_t cx, cy;
};



void drawFace(char* command, char* currentPath, Disk& disk)
{
    x86_Initiate_Video_Mode();

    const int r = 60;
    const int diamter = 2 * r;
    const int squaredRad = r * r;
    const int smallerCircleR = 10;
    const int smallerCircleDiam = 2 * smallerCircleR;
    const int smallerCircleSquaredRad = smallerCircleR * smallerCircleR;


    Point p[500]; //Buffer for efficence 
    int index = 0;

    for (int i = 0; i <= diamter; ++i)
    {
        for (int j = 0; j <= diamter; ++j)
        {
            int dx = j - r;
            int dy = i - r;

            int squaredDistance = dx * dx + dy * dy;

            if (squaredDistance <= squaredRad + r)
            {
                Point np;
                np.cx = i;
                np.cy = j;
                p[index] = np;

                ++index;
                if (index == 500)
                {
                    for (int i = 0; i < index; ++i)
                    {
                        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_RED);
                    }
                    index = 0;
                }
            }
        }

    }

    for (int i = 0; i < index; ++i)
    {
        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_RED);
    }
    
    Point empty;
    empty.cx = -1;
    empty.cy = -1;

    unsigned int size = 500;
    fill(p, 500, empty);

    for (int i = 0; i <= diamter; ++i)
    {
        for (int j = 0; j <= diamter; ++j)
        {
            int dx = j - 30;
            int dy = i - 30;

            int dy2 = i - 80;

            int squaredDistance = dx * dx + dy * dy;
            int squaredDistance2 = dx * dx + dy2 * dy2;

            if (squaredDistance <= smallerCircleSquaredRad + smallerCircleR || squaredDistance2 <= smallerCircleSquaredRad + smallerCircleR)
            {
                Point np;
                np.cx = i;
                np.cy = j;
                p[index] = np;

                ++index;
                if (index == 500)
                {
                    for (int i = 0; i < index; ++i)
                    {
                        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_BLACK);
                    }
                    index = 0;
                }
            }
        }

    }
    for (int i = 0; i < index; ++i)
    {
        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_BLACK);
    }

    fill(p, 500, empty);

    for (int i = 0; i <= diamter; ++i)
    {
        for (int j = 0; j <= diamter; ++j)
        {
            int dx = j - 80;
            int dy = i - 55;

            int squaredDistance = dx * dx + dy * dy;

            if (squaredDistance <= smallerCircleSquaredRad + smallerCircleR + 20)
            {
                Point np;
                np.cx = i;
                np.cy = j;
                p[index] = np;

                ++index;
                if (index == 500)
                {
                    for (int i = 0; i < index; ++i)
                    {
                        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_BLACK);
                    }
                    index = 0;
                }
            }
        }

    }
    for (int i = 0; i < index; ++i)
    {
        x86_Draw_Pixel(p[i].cx, p[i].cy, COLOR_BLACK);
    }

    x86_Wait_Keyboard_Input();
    x86_Exit_Video_Mode();
}