#pragma once
#include <map>
#include <string>

enum ValueType
{
	Register,
	LiteralNum,
	LiteralStr,
	MRD,
	Eof
};

struct Value
{
	static const std::map<std::string, Value> cache;
	const ValueType type;
	const void* value;

	Value(ValueType type, const void* value)
		: type(type),
		  value(value)
	{
	}
};

struct ValueBase
{
};
