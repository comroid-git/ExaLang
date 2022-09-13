#pragma once
#include <map>
#include <string>
#include <any>

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
	const std::any* value;

	Value(ValueType type, const std::any* value)
		: type(type),
		  value(value)
	{
	}

	static Value* create(ValueType type, const std::any* value)
	{
		return new Value(type, value);
	}
};
