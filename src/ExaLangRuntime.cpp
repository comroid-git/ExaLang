#include "ExaLangRuntime.h"

#include <thread>
#include <filesystem>

#include "ANTLRInputStream.h"
#include "antlr/CodeVisitor.h"
#include "stmt/StatementBase.h"
#include "ExaLangLexer.h"
#include "ExaLangParser.h"

using namespace std;
using namespace std::chrono;

void ExaLangRuntime::stdIoMode() const
{
	const auto stack = new ExaStack();
	bool active = true;
	string code;
	while (active)
	{
		cout << "exa@" << filesystem::current_path() << ">";
		getline(cin, code);

		if (code == "exit")
			active = false;

		auto parser = makeParser(code.c_str());
		auto binary = CodeVisitor().visit(parser.file()).as<vector<StatementBase>*>();

		auto start = system_clock::now().time_since_epoch();
		stack->runCode(this, binary);
		auto end = system_clock::now().time_since_epoch();
		cout << "[" << (duration_cast<microseconds>(end).count() - duration_cast<microseconds>(start).count()) / 1000.0 << "ms]" << endl;
	}
}

void ExaLangRuntime::runFiles(char** args) const
{
	for (int i = 1; sizeof args > i; i++)
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

ExaLangParser ExaLangRuntime::makeParser(const char* line) const
{
	const auto input = new antlr4::ANTLRInputStream(line);
	const auto lexer = new ExaLangLexer(input);
	const auto tokens = new antlr4::CommonTokenStream(lexer);
	return ExaLangParser(tokens);
}

void ExaLangRuntime::runCode(const char* line) const
{
	auto parser = makeParser(line);
	auto visitor = new CodeVisitor();
	vector<StatementBase>* code = &visitor->visit(parser.file()).as<vector<StatementBase>>();
	const auto stack = new ExaStack();
	stack->runCode(this, code);
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
