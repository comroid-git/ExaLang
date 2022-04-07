// ExaLang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ExaLangRuntime.h"
#include "Value.h"
#include "ExaLangLexer.h"
#include "ExaLangParser.h"

const std::map<std::string, Value*>* Value::cache = new std::map<std::string, Value*>();
const Value* Value::Zero = Value::create(LiteralNum, reinterpret_cast<const void*>(0));
const Value* Value::One = Value::create(LiteralNum, reinterpret_cast<const void*>(1));

int main(int argc, char** args)
{
	std::cout << "In honor of Zachtronics" << std::endl;

	const auto vm = ExaLangRuntime();

	if (argc == 1)
		vm.stdIoMode();
	else vm.runFiles(args);
}
