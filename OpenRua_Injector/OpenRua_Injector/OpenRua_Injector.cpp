#include <iostream>
#include "memory.hpp"

int main()
{
    assert(memory::open("RobloxPlayerBeta.exe"), "Please open roblox");
    printf("PID: %X\n", memory::getpid());
}