#pragma once
#include "antlr/CodeVisitor.h"
#include "ExaStack.h"
#include "Value.h"

class ExaLangRuntime
{
public:
	static ExaLangRuntime* instance;
	const Value* M;

	explicit ExaLangRuntime()
	{
		instance = this;
		const Value value(MRD, nullptr);
		M = &value;
	}

	ExaLangParser makeParser(const char* line) const;
	void stdIoMode() const;
	void runFiles(char**) const;
	void runFile(char*) const;
	void runCode(const char*) const;
	Value read(ExaStack&, Value*) const;
};

