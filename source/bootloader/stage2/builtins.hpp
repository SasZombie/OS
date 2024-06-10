#pragma once
#include "oioperations.hpp"
#include "disk.hpp"
#include "filestream.hpp"
#include "colors.hpp"

void clear(char* command, char* currentPath, Disk &disk);
void help(char* command, char* currentPath, Disk &disk);
void ls(char* command, char* currentPath, Disk &disk);
void cd(char* command, char* currentPath, Disk &disk);
void pwd(char* command, char* currentPath, Disk &disk);
void cat(char* command, char* currentPath, Disk &disk);
void drawFace(char* command, char* currentPath, Disk &disk);
void drawPixels(char* command, char* currentPath, Disk &disk);
void drawSymbal(char* command, char* currentPath, Disk &disk);