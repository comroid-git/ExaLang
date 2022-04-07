#include "ExaStack.h"

#include "StatementBase.h"

void ExaStack::runCode(ExaLangRuntime vm, vector<StatementBase>* code)
{
	this->code = code;
	for (codeIndex = 0; codeIndex < code->size(); codeIndex++)
		code->at(codeIndex).evaluate(vm, *this, &codeIndex);
}

Value* ExaStack::read(const char c)
{
	return regs->at(toupper(c));
}

void ExaStack::write(char c, Value* v)
{
	regs->insert(pair<char, Value*>(c, v));
}

Value* ExaStack::isEof(	)
{
	return const_cast<Value*>(regs->at('f')->value == nullptr ? Value::Zero : Value::One);
}
