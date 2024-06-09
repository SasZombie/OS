#include "oioperations.hpp"
#include "filestream.hpp"
#include "disk.hpp"
#include "shell.hpp"

#define NULL ((void*)0)

const unsigned int cursorHeight = 7;
const unsigned int cursorWidth = 2;

void drawRect(unsigned int row, unsigned int col, unsigned int color)
{
    for (unsigned int i = row; i < row + cursorWidth; ++i)
    {
        for (unsigned int j = col; j < col + cursorHeight; ++j)
        {
            x86_Draw_Pixel(i, j, color);
        }
    }
}


extern "C" {
    void _cdecl cstart_(unsigned short bootDrive)
    {
        x86_Initiate_Video_Mode();

        unsigned int prevPosX = 1;
        unsigned int prevPosY = 1;
        unsigned int x = 0; //Get Cursor X
        unsigned int y = 0; //Get Cursor Y
        unsigned int currentColor = COLOR_WHITE;
        while (true)
        {
            drawRect(x, y, currentColor);
            drawRect(prevPosX, prevPosY, COLOR_BLACK);
            char color;
            // cin(color);
            x86_Read_Character(&color);
            // cout(color);
            prevPosX = x;
            prevPosY = y;
            switch (color)
            {
            case '3':
                currentColor = COLOR_GREEN;
                break;
            case 'w':
                if (y != 0)
                    --y;
                break;
            case 'a':
                if (x != 0)
                    --x;
                break;
            case 's':
                ++y;
                break;
            case 'd':
                ++x;
                break;
            case 'f':
                x86_Draw_Pixel(x, y, currentColor);

            default:
                break;
            }

            // cout(x);
            cout(y);
            // x86_Wait_Keyboard_Input();

            // x = x + 10;
            // y = y + 10;
            // x86_Wait_Keyboard_Input();
        }
        // int c = 0;
        // cin(c);
        // cout(c);
        // startShell("sas", bootDrive);
        // cout("\nEND");
    }
}