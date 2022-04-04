#include "CodeVisitor.h"

#include "StatementBase.h"
#include "antlr_generated/ExaLangLexer.h"

antlrcpp::Any CodeVisitor::visitFile(ExaLangParser::FileContext* ctx)
{
	std::vector<StatementBase> yield;
	for (auto stmt : ctx->stmt())
	{
		auto out = this->visitStmt(stmt);
		yield.push_back(out.as<StatementBase>());
	}
	return yield;
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
	throw std::exception(std::string("Invalid context: " + ctx->getText()).c_str());
}

antlrcpp::Any CodeVisitor::visitStmtUnary(ExaLangParser::StmtUnaryContext* ctx)
{
	switch (ctx->start->getType())
	{
	case ExaLangLexer::MARK: break;
	case ExaLangLexer::JUMP: break;
	case ExaLangLexer::TJMP: break;
	case ExaLangLexer::FJMP: break;
	case ExaLangLexer::REPL: break;
	case ExaLangLexer::LINK: break;
	case ExaLangLexer::HOST: break;
	case ExaLangLexer::VOID: break;
	case ExaLangLexer::GRAB: break;
	case ExaLangLexer::FILE: break;
	case ExaLangLexer::SEEK: break;
	default: break;
	}
	throw std::exception(std::string("Invalid context: " + ctx->getText()).c_str());
}

antlrcpp::Any CodeVisitor::visitStmtBinary(ExaLangParser::StmtBinaryContext* ctx)
{
	switch (ctx->start->getType())
	{
	case ExaLangLexer::COPY: break;
	default: break;
	}
	throw std::exception(std::string("Invalid context: " + ctx->getText()).c_str());
}

antlrcpp::Any CodeVisitor::visitStmtTrinary(ExaLangParser::StmtTrinaryContext* ctx)
{
	switch (ctx->start->getType())
	{
	case ExaLangLexer::SWIZ: break;
	case ExaLangLexer::RAND: break;
	case ExaLangLexer::ADDI: break;
	case ExaLangLexer::SUBI: break;
	case ExaLangLexer::MULI: break;
	case ExaLangLexer::DIVI: break;
	case ExaLangLexer::MODI: break;
	default: break;
	}
	throw std::exception(std::string("Invalid context: " + ctx->getText()).c_str());
}

antlrcpp::Any CodeVisitor::visitTestCompare(ExaLangParser::TestCompareContext* ctx)
{
	auto left = visit(ctx->var(0));
	auto right = visit(ctx->var(1));
	int op;
	switch (ctx->COMP_OP()->getSymbol()->getType())
	{
	case ExaLangLexer::EQUALS: op = 0; break;
	case ExaLangLexer::NOTEQUALS: op = 1; break;
	case ExaLangLexer::LESSER: op = 2; break;
	case ExaLangLexer::GREATER: op = 3; break;
	default: throw std::exception(std::string("Invalid operator: " + ctx->COMP_OP()->getText()).c_str());
	}
	// todo: Return Statement
}

antlrcpp::Any CodeVisitor::visitTestMrd(ExaLangParser::TestMrdContext* ctx)
{
	// todo: Return Statement
}

antlrcpp::Any CodeVisitor::visitTestEof(ExaLangParser::TestEofContext* ctx)
{
	// todo: Return Statement
}

antlrcpp::Any CodeVisitor::visitVar(ExaLangParser::VarContext* ctx)
{
	// todo: Return Statement
}
