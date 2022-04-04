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
	void evaluate(ExaLangRuntime vm, ExaStack& stack) override
	{
		auto left = vm.read(stack, this->left);
		auto right = vm.read(stack, this->right);
		switch (op)
		{
		case 0: // equals
			break;
		case 1: // not equals
			break;
		case 2: // lesser
			break;
		case 3: // greater
			break;
		}
	}
};
