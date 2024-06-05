#pragma once
#include "oioperations.hpp"
#include "disk.hpp"
#include "filestream.hpp"

void clear(char*** args, Disk& disk);
void help(char*** args, Disk& disk);
void ls(char*** args, Disk& disk);
void cd(char*** args, Disk& disk);
void pwd(char*** args, Disk& disk);