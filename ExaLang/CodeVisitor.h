#pragma once
#include "AbstractVisitor.h"

class CodeVisitor : public ExaLangBaseVisitor
{
public:
	antlrcpp::Any visitFile(ExaLangParser::FileContext* ctx) override;
	antlrcpp::Any visitStmtBlank(ExaLangParser::StmtBlankContext* ctx) override;
	antlrcpp::Any visitStmtUnary(ExaLangParser::StmtUnaryContext* ctx) override;
	antlrcpp::Any visitStmtBinary(ExaLangParser::StmtBinaryContext* ctx) override;
	antlrcpp::Any visitStmtTrinary(ExaLangParser::StmtTrinaryContext* ctx) override;
	antlrcpp::Any visitTestCompare(ExaLangParser::TestCompareContext* ctx) override;
	antlrcpp::Any visitTestMrd(ExaLangParser::TestMrdContext* ctx) override;
	antlrcpp::Any visitTestEof(ExaLangParser::TestEofContext* ctx) override;
	antlrcpp::Any visitVarReg(ExaLangParser::VarRegContext* context) override;
	antlrcpp::Any visitVarNum(ExaLangParser::VarNumContext* context) override;
	antlrcpp::Any visitVarStr(ExaLangParser::VarStrContext* context) override;
};

