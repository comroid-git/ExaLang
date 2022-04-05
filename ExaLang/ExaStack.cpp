#include "ExaStack.h"

Value* ExaStack::read(const char c)
{
	return regs.at(std::toupper(c));
}

void ExaStack::write(const char c, Value v)
{
	regs.insert()
	regs.insert(std::pair<const char, Value>(c, v));
}

Value* ExaStack::isEof()
{
	return const_cast<Value*>(regs.at('f')->value == nullptr ? Value::Zero : Value::One);
}
