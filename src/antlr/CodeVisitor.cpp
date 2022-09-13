#include "CodeVisitor.h"

#include "../stmt/StatementBase.h"
#include "../stmt/StatementTestOp.h"
#include "ExaLangLexer.h"

antlrcpp::Any CodeVisitor::visitFile(ExaLangParser::FileContext* ctx)
{
	std::vector<StatementBase> yield;
	for (auto stmt : ctx->stmt())
	{
		any out = this->visitStmt(stmt);
		yield.push_back(any_cast<StatementBase>(out));
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
	throw std::string("Invalid context: " + ctx->getText());
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
	throw std::string("Invalid context: " + ctx->getText());
}

antlrcpp::Any CodeVisitor::visitStmtBinary(ExaLangParser::StmtBinaryContext* ctx)
{
	switch (ctx->start->getType())
	{
	case ExaLangLexer::COPY: break;
	default: break;
	}
	throw std::string("Invalid context: " + ctx->getText());
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
	throw std::string("Invalid context: " + ctx->getText());
}

antlrcpp::Any CodeVisitor::visitTestCompare(ExaLangParser::TestCompareContext* ctx)
{
	auto left = any_cast<Value*>(visit(ctx->var(0)));
	auto right = any_cast<Value*>(visit(ctx->var(1)));
	int op;
	switch (ctx->COMP_OP()->getSymbol()->getType())
	{
	case ExaLangLexer::EQUALS: op = 0; break;
	case ExaLangLexer::NOTEQUALS: op = 1; break;
	case ExaLangLexer::LESSER: op = 2; break;
	case ExaLangLexer::GREATER: op = 3; break;
	default: throw std::string("Invalid operator: " + ctx->COMP_OP()->getText());
	}
	return StatementTestOp(left, right, op);
}

antlrcpp::Any CodeVisitor::visitTestMrd(ExaLangParser::TestMrdContext* ctx)
{
	Value* value = Value::create(MRD, nullptr);
	return value;
}

antlrcpp::Any CodeVisitor::visitTestEof(ExaLangParser::TestEofContext* ctx)
{
	Value* value = Value::create(Eof, nullptr);
	return value;
}

antlrcpp::Any CodeVisitor::visitVarReg(ExaLangParser::VarRegContext* context)
{
	char reg = context->start->getText()[0];
    std::any it = reg;
	Value* value = Value::create(Register, &it);
	return value;
}

antlrcpp::Any CodeVisitor::visitVarNum(ExaLangParser::VarNumContext* context)
{
	double num = atof(context->start->getText().c_str());
    std::any it = num;
	Value* value = Value::create(LiteralNum, &it);
	return value;
}

antlrcpp::Any CodeVisitor::visitVarStr(ExaLangParser::VarStrContext* context)
{
	std::string str = context->start->getText();
	str = str.substr(1, str.length() - 2);
    std::any it = str;
	Value* value = Value::create(LiteralStr, &it);
	return value;
}
