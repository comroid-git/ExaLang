#pragma once
#include "StatementBase.h"
class StatementBlank :
    public StatementBase
{
public:
	void evaluate(ExaLangRuntime, ExaStack&) override;
};

