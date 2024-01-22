#include "compiler.hpp"
#include "compiler/Luau/BytecodeBuilder.h"
#include "compiler/Luau/Compiler.h"
#include <zstd.h>   // .\vcpkg install zstd
#include <xxhash.h> // .\vcpkg install xxhash

Luau::CompileOptions options = {
	.optimizationLevel = 2
};

std::string compile(std::string src) 
{
	std::string bytecode = Luau::compile(src, options);
	if (bytecode.at(0) == 0)
		return bytecode;
	std::string output = "RSB1";
	std::size_t dataSize = bytecode.size();
	std::size_t maxSize = ZSTD_compressBound(dataSize);
	std::vector<char> compressed(maxSize);
	std::size_t compSize = ZSTD_compress(&compressed[0], maxSize, bytecode.c_str(), dataSize, ZSTD_maxCLevel());
	output.append(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
	output.append(&compressed[0], compSize);
	std::uint32_t firstHash = XXH32(&output[0], output.size(), 42U);
	std::uint8_t hashedBytes[4];
	std::memcpy(hashedBytes, &firstHash, sizeof(firstHash));
	for (std::size_t i = 0; i < output.size(); ++i)
		output[i] ^= hashedBytes[i % 4] + i * 41U;
	return output;
}