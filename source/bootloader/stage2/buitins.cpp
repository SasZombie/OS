#include "builtins.hpp"

void clear(const char* args)
{
    (void)args;
    
    x86_Clear_Screen();
}

void help(const char* args)
{
    (void)args;
    cout("Type a command. Commadns are: \n\t help \n\t clear");
}