#pragma once
#include <string>

class Operand
{
public:

	enum class OperandType
	{
		FunctionIdentifier,
		FunctionExpression,
		Variable
	};

	virtual OperandType GetType() const = 0;
	virtual std::string GetIdentifier() const = 0;

	static bool IsCorrectIdentifier(const std::string& identifier);

	virtual ~Operand() = default;

};