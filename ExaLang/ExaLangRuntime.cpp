#include "ExaLangRuntime.h"

#include <thread>
#include <filesystem>

#include "ANTLRInputStream.h"
#include "CodeVisitor.h"
#include "StatementBase.h"
#include "antlr_generated/ExaLangLexer.h"
#include "antlr_generated/ExaLangParser.h"

using namespace std;

void ExaLangRuntime::stdIoMode() const
{
	bool active = true;
	auto stack = new ExaStack();
	string code;
	while (active)
	{
		cout << "exa @ " << filesystem::current_path() << ">";
		getline(cin, code);
		this->runCode(code.c_str());
	}
}

void ExaLangRuntime::runFiles(char** args) const
{
	for (int i = 1; i < sizeof(args); i++)
	{
		thread([args, i, this]
			{
				this->runFile(args[i]);
			}).detach();
	}
}

void ExaLangRuntime::runFile(char* fname) const
{
	ifstream read(fname);
	stringstream buf;
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
	vector<StatementBase>* code = &visitor->visit(parser->file()).as<vector<StatementBase>>();
	const auto stack = new ExaStack();
	stack->runCode(code);
}

Value ExaLangRuntime::read(ExaStack& stack, Value* value) const
{
	char c = *static_cast<const char*>(value->value);
	switch (value->type)
	{
	case Register:
		c = toupper(c);
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
	throw exception("invalid state");
}
