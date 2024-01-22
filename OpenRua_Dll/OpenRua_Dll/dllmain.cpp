#include <Windows.h>
#include <iostream>
#include "execution.hpp"

/* 
    HELLO, AND WELCOME TO THE DLLMAIN.CPP! 
    THERE ARE 2 VCPKG LIBS YOU NEED TO HAVE:
        zstd
        xxhash
    ALL INSTALLED BY:
        launch cmd
        go to your user
        then enter these cmds:
            cd vcpkg
            vcpkg install zstd
            vcpkg install xxhash
*/

void load()
{
    execution::begin();
    execution::execute("print('Hello World!')");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == 1)
        load(); 
    return TRUE;
}