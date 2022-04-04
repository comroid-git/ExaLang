#include "CodeVisitor.h"

#include "antlr_generated/ExaLangLexer.h"

antlrcpp::Any CodeVisitor::visitFile(ExaLangParser::FileContext* context)
{
	for (auto stmt : context->stmt())
		visitStmt(stmt);
	return NULL;
}

antlrcpp::Any CodeVisitor::visitStmtBlank(ExaLangParser::StmtBlankContext* ctx)
{
	switch (ctx->start->getType())
	{
	case ExaLangLexer::HALT: break;
	case ExaLangLexer::KILL: break;
	case ExaLangLexer::MODE: break;
	case ExaLangLexer::MAKE: break;
	case ExaLangLexer::DROP: break;
	case ExaLangLexer::WIPE: break;
	case ExaLangLexer::NOOP: break;
	default: break;
	}
	return NULL;
}

antlrcpp::Any CodeVisitor::visitStmtUnary(ExaLangParser::StmtUnaryContext* ctx)
{
	return ExaLangBaseVisitor::visitStmtUnary(ctx);
}

antlrcpp::Any CodeVisitor::visitStmtBinary(ExaLangParser::StmtBinaryContext* ctx)
{
	return ExaLangBaseVisitor::visitStmtBinary(ctx);
}

antlrcpp::Any CodeVisitor::visitStmtTrinary(ExaLangParser::StmtTrinaryContext* ctx)
{
	return ExaLangBaseVisitor::visitStmtTrinary(ctx);
}

antlrcpp::Any CodeVisitor::visitStmtSpecial(ExaLangParser::StmtSpecialContext* ctx)
{
	return ExaLangBaseVisitor::visitStmtSpecial(ctx);
}

antlrcpp::Any CodeVisitor::visitVar(ExaLangParser::VarContext* ctx)
{
	return ExaLangBaseVisitor::visitVar(ctx);
}
