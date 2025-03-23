#pragma once
#include <string>
#include "Operand.h"

class Variable final :
	public Operand
{
public:
	Variable(std::string identifier, double value = std::numeric_limits<double>::quiet_NaN());

	OperandType Operand::GetType() const override;
	std::string GetIdentifier() const override;
	double GetValue() const;
	void SetValue(double value);

private:
	std::string m_identifier;
	double m_value;
};
