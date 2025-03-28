#pragma once
#include "Operand.h"

class CFunctionIdentifier final :
	public COperand
{
public:
	CFunctionIdentifier(std::string const& identifier, std::string const& operand);

	OperandType COperand::GetType() const override;
	std::string GetIdentifier() const override;
	std::string GetOperand() const;

private:
	std::string m_identifier;
	std::string m_operand;
};