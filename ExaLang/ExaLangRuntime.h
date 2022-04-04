#pragma once
class ExaLangRuntime
{
public:
	void stdIoMode() const;
	void runFiles(char** files) const;
	void runFile(char* fname) const;
	void runCode(const char* code) const;
};

