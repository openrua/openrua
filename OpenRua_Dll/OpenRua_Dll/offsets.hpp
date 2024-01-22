#pragma once
#include <Windows.h>
#include <string>

/* version-75acb088f43843cf */

static uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
namespace offsets
{
	static uintptr_t luavm_load = base + 0xBECDC0;
	static uintptr_t task_spawn = base + 0xDF8CE0;
	static uintptr_t get_state = base + 0xBDA100;

	namespace state
	{
		constexpr int top = 0x28;
	}

	namespace tstring
	{
		constexpr int data = 0x18;
	}
}

static auto luavm_load = reinterpret_cast<int(__fastcall*)(uintptr_t L, std::string* bytecode, const char* chunk, int env)>(offsets::luavm_load);
static auto task_spawn = reinterpret_cast<int(__cdecl*)(uintptr_t L)>(offsets::task_spawn);
static auto get_state = reinterpret_cast<uintptr_t(__fastcall*)(uintptr_t sc, int* wowza1, int* wowza2)>(offsets::get_state);