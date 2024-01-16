#include "memory.hpp"

DWORD pid;
HANDLE proc;

namespace memory
{
	bool open(const char* name)
	{
		HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		assert(snap != INVALID_HANDLE_VALUE, "Failed to open process snapshot!");

		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(pe);

		assert(Process32First(snap, &pe), "Failed to get first process!");

		do
		{
			if (strcmp(pe.szExeFile, name) == 0)
			{
				pid = pe.th32ProcessID;
				proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
				CloseHandle(snap);
				return true;
			}
		} while (Process32Next(snap, &pe));
		CloseHandle(snap);

		return false;
	}

	HANDLE getproc()
	{
		return proc;
	}

	DWORD getpid()
	{
		return pid;
	}

	uint8_t readByte(uintptr_t address)
	{
		uint8_t res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	int readInt(uintptr_t address)
	{
		int res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	unsigned int readUInt(uintptr_t address)
	{
		unsigned int res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	DWORD readDword(uintptr_t address)
	{
		DWORD res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	uintptr_t readQword(uintptr_t address)
	{
		uintptr_t res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	double readDouble(uintptr_t address)
	{
		double res;
		ReadProcessMemory(proc, (LPVOID)address, &res, sizeof(res), 0);
		return res;
	}

	uint8_t* readBytes(uintptr_t address, size_t count)
	{
		uint8_t* res = (uint8_t*)malloc(count);
		ReadProcessMemory(proc, (LPVOID)address, res, count, 0);
		return res;
	}


	void writeByte(uintptr_t address, uint8_t v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeInt(uintptr_t address, int v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeUInt(uintptr_t address, unsigned int v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeDword(uintptr_t address, DWORD v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeQword(uintptr_t address, uintptr_t v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeDouble(uintptr_t address, double v)
	{
		WriteProcessMemory(proc, (LPVOID)address, &v, sizeof(v), 0);
	}

	void writeBytes(uintptr_t address, uint8_t* v, size_t count)
	{
		WriteProcessMemory(proc, (LPVOID)address, v, count, 0);
	}
}