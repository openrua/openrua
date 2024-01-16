#include <Windows.h>
#include <iostream>
#include "compiler.hpp"

void load()
{
    
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == 1)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)load, 0, 0, 0);
    return TRUE;
}