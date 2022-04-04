#pragma once
#include "antlr_generated/ExaLangBaseVisitor.h"

struct AbstractVisitor : ExaLangBaseVisitor
{
protected:
	bool shouldVisitNextChild(antlr4::tree::ParseTree*, const antlrcpp::Any& result) override;
};
