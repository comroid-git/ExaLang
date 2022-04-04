#pragma once
#include "ExaStack.h"
#include "ValueBase.h"

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

	void stdIoMode() const;
	void runFiles(char**) const;
	void runFile(char*) const;
	void runCode(const char*) const;
	Value read(ExaStack&, Value*) const;
};

