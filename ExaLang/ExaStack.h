#pragma once

#include <vector>

#include "ExaLangRuntime.h"
#include "Value.h"

struct StatementBase;
using namespace std;

class ExaStack
{
public:
	map<char, Value*>* regs;
	vector<StatementBase>* code;
	int codeIndex;

	void runCode(ExaLangRuntime, vector<StatementBase>*);

	Value* read(char);
	void write(char, Value*);
	Value* isEof();
};

