#include "compiler.hpp"
#include "compiler/Luau/BytecodeBuilder.h"
#include "compiler/Luau/Compiler.h"

Luau::CompileOptions options = {
	.optimizationLevel = 2
};

/* NOTE: no need for bytecode encoder, i already added it to the Luau.Compiler.lib */
std::string compile(std::string src) 
{
	return Luau::compile(src, options);
}