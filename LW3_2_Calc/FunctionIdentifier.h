#pragma once
#include "Operand.h"

class CFunctionIdentifier final :
	public COperand
{
public:
	CFunctionIdentifier(std::string identifier, std::string operand);

	OperandType COperand::GetType() const override;
	std::string GetIdentifier() const override;


private:
	std::string m_identifier;
	std::string m_operand;
};
