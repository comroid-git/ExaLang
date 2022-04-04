// ExaLang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ExaLangRuntime.h"
#include "ValueBase.h"
#include "antlr_generated/ExaLangLexer.h"
#include "antlr_generated/ExaLangParser.h"

const std::map<std::string, Value> Value::cache = std::map<std::string, Value>();

int main(int argc, char** args)
{
	std::cout << "In honor of Zachtronics" << std::endl;

	const auto vm = ExaLangRuntime();

	if (argc == 1)
		vm.stdIoMode();
	else vm.runFiles(args);
}
