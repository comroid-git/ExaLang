#include "ExaLangRuntime.h"

#include <thread>

#include "ANTLRInputStream.h"
#include "CodeVisitor.h"
#include "StatementBase.h"
#include "antlr_generated/ExaLangLexer.h"
#include "antlr_generated/ExaLangParser.h"

void ExaLangRuntime::stdIoMode() const
{
}

void ExaLangRuntime::runFiles(char** args) const
{
	for (int i = 1; i < sizeof(args); i++)
	{
		std::thread([args, i, this]
			{
				this->runFile(args[i]);
			}).detach();
	}
}

void ExaLangRuntime::runFile(char* fname) const
{
	std::ifstream read(fname);
	std::stringstream buf;
	buf << read.rdbuf();
	read.close();
	this->runCode(buf.str().c_str());
}

void ExaLangRuntime::runCode(const char* line) const
{
	const auto input = new antlr4::ANTLRInputStream(line);
	const auto lexer = new ExaLangLexer(input);
	const auto tokens = new antlr4::CommonTokenStream(lexer);
	const auto parser = new ExaLangParser(tokens);
	const auto visitor = new CodeVisitor();
	const std::vector<StatementBase> code = visitor->visit(parser->file()).as<std::vector<StatementBase>>();
	const auto stack = new ExaStack();
	for (auto stmt : code)
		stmt.evaluate(*this, *stack);
}

Value ExaLangRuntime::read(ExaStack& stack, Value* value) const
{
	char c = *static_cast<const char*>(value->value);
	switch (value->type)
	{
	case Register:
		c = std::toupper(c);
		if (c == 'M')
			return *M;
		return *stack.read(c);
	case LiteralNum:
	case LiteralStr:
		return *value;
	case MRD:
		return *M;
	case Eof:
		return *stack.isEof();
	}
	throw std::exception("invalid state");
}
