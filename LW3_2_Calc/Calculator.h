#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>

enum class ErrorDescription
{
	UnknownCommand,		// ���� ������� ����������� �������
	InvalidUsage,		// ���� ��������� ��������� ������� �� ������������� �������� (� ��� ����� ������������ �������������)
	DuplicateName,		// ���� ���������� � ����� ������ ��� ���� ���������
	NameNotExist,		// ���� � ������� ������������ ������������� ����������
	NotNumberEntered,	// ���� ������������� �� �����
	IncorrectIdentifier,
	NoError			
};

static const std::map<std::string, ErrorDescription> ERROR_DESCRIPRTION
{
	{ "Unknown command", ErrorDescription::UnknownCommand },
	{ "Invalid usage", ErrorDescription::InvalidUsage },
	{ "Name already exists", ErrorDescription::DuplicateName },
	{ "Name does not exist", ErrorDescription::NameNotExist },
	{ "Not a number entered", ErrorDescription::NotNumberEntered},
	{ "Incorrect identifier", ErrorDescription::IncorrectIdentifier }
};

class CCalculator
{
public:
	CCalculator();

	bool DeclareVariable(const std::string& identifier);
	bool DeclareFunction(const std::string& identifier, const std::string& expression);

	bool CheckIdentifier(const std::string& identifier);

	bool IsOperandDeclared(const std::string& identifier) const;
	
	bool SetVariableValue(std::string identifier, std::string newValue);
	
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);
	//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
	std::optional<std::reference_wrapper<COperand>> GetOperandRef(const std::string& identifier) const;
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

private:
	// ��� ������ �������� � pablic
	//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
	//std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);
	
	//std::optional<std::unique_ptr<COperand>*> GetOperandRef(const std::string& identifier);
	//std::optional<COperand*> GetOperandRef(const std::string& identifier) const;
	

	std::vector<std::unique_ptr<COperand>> m_operands;
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

