#pragma once
#include "oioperations.hpp"
#include "cstring.hpp"
#include "builtins.hpp"
#include "filestream.hpp"

void startShell(const char* name, unsigned short bootDrive);
void validateCommand(const char* command);