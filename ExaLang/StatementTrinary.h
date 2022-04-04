#pragma once
#include "StatementBase.h"
class StatementTrinary :
	public StatementBase
{
public:
	void evaluate(ExaLangRuntime, ExaStack&) override;
};
