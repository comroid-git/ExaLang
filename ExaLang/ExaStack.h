#pragma once

#include "Value.h"

class ExaStack
{
public:
	const std::map<const char, Value*> regs;

	explicit ExaStack(): regs(std::map<const char, Value*>())
	{
	}

	Value* read(const char);
	void write(const char, Value);
	Value* isEof();
};

