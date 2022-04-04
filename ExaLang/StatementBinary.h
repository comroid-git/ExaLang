#pragma once
#include "StatementBase.h"
class StatementBinary :
    public StatementBase
{
public:
	void evaluate(ExaLangRuntime, ExaStack&) override;
};

