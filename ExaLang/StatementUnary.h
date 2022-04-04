#pragma once
#include "StatementBase.h"
class StatementUnary :
    public StatementBase
{
public:
	void evaluate(ExaLangRuntime, ExaStack&) override;
};

