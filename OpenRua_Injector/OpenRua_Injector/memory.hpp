#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string>

namespace memory
{
	bool open(const char* name);

	HANDLE getproc();
	DWORD getpid();

	uint8_t readByte(uintptr_t address);
	int readInt(uintptr_t address);
	unsigned int readUInt(uintptr_t address);
	DWORD readDword(uintptr_t address);
	uintptr_t readQword(uintptr_t address);
	double readDouble(uintptr_t address);
	uint8_t* readBytes(uintptr_t address, size_t count);

	void writeByte(uintptr_t address, uint8_t b);
	void writeInt(uintptr_t address, int i);
	void writeUInt(uintptr_t address, unsigned int i);
	void writeDword(uintptr_t address, DWORD d);
	void writeQword(uintptr_t address, uintptr_t q);
	void writeDouble(uintptr_t address, double d);
	void writeBytes(uintptr_t address, uint8_t* buffer, size_t count);
}

#define assert(cond, msg, extra_code) if (!(cond)) \
{ \
	if (memory::getpid()) \
		CloseHandle(memory::getproc()); \
	extra_code; \
	printf("%s\nPress any key to exit...", msg); \
	system("pause > nul"); \
	exit(1); \
}