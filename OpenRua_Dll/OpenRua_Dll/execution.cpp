#define _CRT_SECURE_NO_WARNINGS

#include "offsets.hpp"
#include "execution.hpp"
#include "offsets.hpp"
#include "compiler.hpp"
#include <unordered_map>
#include <filesystem>
#include <fstream>

typedef union
{
	uintptr_t gc;
	void* p;
	double n;
	int b;
	float v[2];
} Value;

typedef struct lua_tvalue
{
	Value value;
	int extra[1];
	int tt;
} lua_TValue;

uintptr_t datamodel;
uintptr_t sc;

void dump_datamodel()
{
	std::string _path = getenv("LOCALAPPDATA");
	_path += "\\Roblox\\logs";
	while (true)
	{
		printf("Loop step\n");
		bool first = true;
		std::string path;
		std::filesystem::file_time_type less;

		for (std::filesystem::directory_entry file : std::filesystem::directory_iterator(_path))
		{
			std::string raw_path = file.path().string();
			if (raw_path.find("Player") != std::string::npos)
			{
				std::filesystem::file_time_type last_write = std::filesystem::last_write_time(file.path());
				if (first || less < last_write)
				{
					if (first)
						first = false;
					path = raw_path;
					less = last_write;
				}
			}
		}

		std::vector<uintptr_t> datamodels = {};
		std::ifstream ifile(path);
		while (true)
		{
			std::string content = "";
			std::getline(ifile, content);
			if (content.size() < 1)
				std::getline(ifile, content);
			if (content.size() < 1)
				break;
			size_t pos = content.find("initialized DataModel");
			if (pos != std::string::npos)
				datamodels.push_back(std::stoull(content.substr(pos + 22, 16), nullptr, 16));
		}
		if (datamodels.size() > 0)
		{
			datamodel = datamodels[datamodels.size() - 1];
			break;
		}

		Sleep(1000);
	}
}

namespace execution
{
	void begin()
	{
		dump_datamodel();
		uintptr_t children = *reinterpret_cast<uintptr_t*>(datamodel + 0x50);
		for (uintptr_t child = *reinterpret_cast<uintptr_t*>(children); child < *reinterpret_cast<uintptr_t*>(children); child += 8)
		{
			if (*reinterpret_cast<std::string*>(*reinterpret_cast<uintptr_t*>(child + 0x18) + 0x8) == "ScriptContext")
			{
				sc = child;
				break;
			}
		}
	}
	
	void execute(std::string s)
	{
		uintptr_t L = get_state(sc, nullptr, nullptr);
		std::string bytecode = compile(s);
		if (bytecode.at(0) == 0)
		{
			std::string error = bytecode.substr(1);
			MessageBoxA(0, error.c_str(), "OpenRua", 0);
			return;
		}
		if (luavm_load(L, &bytecode, "@OpenRua", 0) == 0)
			task_spawn(L);
		
		*reinterpret_cast<uintptr_t*>(L + offsets::state::top) -= 16;
	}
}