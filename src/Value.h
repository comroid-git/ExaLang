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
	static const std::map<std::string, Value*>* cache;
	static const Value* Zero;
	static const Value* One;
	const ValueType type;
	const void* value;

	Value(ValueType type, const void* value)
		: type(type),
		  value(value)
	{
	}

	static Value* create(ValueType type, const void* value)
	{
		return new Value(type, value);
	}
};
