#pragma once

#include "StatementBase.h"

class StatementTestOp :
	public StatementBase
{
public:
	Value* left;
	Value* right;
	int op;
	StatementTestOp(Value* left, Value* right, int op) : left(left), right(right), op(op) {}
	void evaluate(ExaLangRuntime* vm, ExaStack& stack, int* codeIndex) override;
};
