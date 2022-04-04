#pragma once
#include "AbstractVisitor.h"

class CodeVisitor : public ExaLangBaseVisitor
{
public:
	antlrcpp::Any visitFile(ExaLangParser::FileContext* context) override;
	antlrcpp::Any visitStmt(ExaLangParser::StmtContext* context) override;
	antlrcpp::Any visitStmtBlank(ExaLangParser::StmtBlankContext* ctx) override;
	antlrcpp::Any visitStmtUnary(ExaLangParser::StmtUnaryContext* ctx) override;
	antlrcpp::Any visitStmtBinary(ExaLangParser::StmtBinaryContext* ctx) override;
	antlrcpp::Any visitStmtTrinary(ExaLangParser::StmtTrinaryContext* ctx) override;
	antlrcpp::Any visitStmtSpecial(ExaLangParser::StmtSpecialContext* ctx) override;
	antlrcpp::Any visitVar(ExaLangParser::VarContext* ctx) override;
};

