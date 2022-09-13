#pragma once
#include "../ExaLangRuntime.h"
#include "../ExaStack.h"

struct StatementBase
{
public:
	virtual void evaluate(const ExaLangRuntime* vm, ExaStack& stack, int* codeIndex);
};

class StatementBlank :
        public StatementBase
{
};
class StatementUnary :
        public StatementBase
{
};
class StatementBinary :
        public StatementBase
{
};
class StatementTrinary :
        public StatementBase
{
};
