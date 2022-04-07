#pragma once
#include "ExaLangRuntime.h"
#include "ExaStack.h"

struct StatementBase
{
public:
	virtual void evaluate(ExaLangRuntime vm, ExaStack& stack, int* codeIndex);
};
