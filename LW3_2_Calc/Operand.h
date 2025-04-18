#pragma once
#include <string>

class COperand
{
public:

	enum class OperandType
	{
		Variable,
		FunctionIdentifier,
		FunctionExpression
	};

	virtual OperandType GetType() const = 0;
	virtual std::string GetIdentifier() const = 0;

	static bool IsCorrectIdentifier(const std::string& identifier);

	virtual ~COperand() = default;

};