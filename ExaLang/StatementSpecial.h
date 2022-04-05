﻿#pragma once

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
		bool result = false;

		switch (op)
		{
		case 0: // equals
			if (left.type == LiteralNum == right.type)
				result = *static_cast<const int*>(left.value) == *static_cast<const int*>(right.value);
			else if (left.type == LiteralStr == right.type)
				result = strcmp(static_cast<const char*>(left.value), static_cast<const char*>(right.value)) == 0;
			break;
		case 1: // not equals
			if (left.type == LiteralNum == right.type)
				result = *static_cast<const int*>(left.value) != *static_cast<const int*>(right.value);
			else if (left.type == LiteralStr == right.type)
				result = strcmp(static_cast<const char*>(left.value), static_cast<const char*>(right.value)) != 0;
			break;
		case 2: // lesser
			if (left.type == LiteralNum == right.type)
				result = *static_cast<const int*>(left.value) < *static_cast<const int*>(right.value);
			break;
		case 3: // greater
			if (left.type == LiteralNum == right.type)
				result = *static_cast<const int*>(left.value) > *static_cast<const int*>(right.value);
			break;
		}

		stack.write('t', result ? *Value::Zero : *Value::One);
	}
};
