#include "ExaStack.h"

Value* ExaStack::read(const char c)
{
	return regs.at(c);
}
