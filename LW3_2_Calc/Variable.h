#pragma once
#include "Operand.h"

class CVariable final :
	public COperand
{
public:
	// «начение переменной после ее объ€влени€ не определено (использовать значение nan дл€ этих целей)
	CVariable(std::string const& identifier, double const& value = std::numeric_limits<double>::quiet_NaN()); //“ихий (quiet)

	OperandType COperand::GetType() const override;
	std::string GetIdentifier() const override;
	double GetValue() const;
	void SetValue(double value);

private:
	std::string m_identifier;
	double m_value;
};
