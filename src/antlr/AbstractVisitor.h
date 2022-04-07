#pragma once
#include "ExaLangParserBaseVisitor.h"
#include "tree/ParseTree.h"

struct AbstractVisitor : ExaLangParserBaseVisitor
{
protected:
	bool shouldVisitNextChild(antlr4::tree::ParseTree*, const antlrcpp::Any& result) override;
};
