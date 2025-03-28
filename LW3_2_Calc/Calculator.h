#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include <algorithm> 
#include <cctype>  

enum class ErrorDescription
{
	UnknownCommand,		// ���� ������� ����������� �������
	InvalidUsage,		// ���� ��������� ��������� ������� �� ������������� �������� (� ��� ����� ������������ �������������)
	DuplicateName,		// ���� ���������� � ����� ������ ��� ���� ���������
	NameNotExist,		// ���� � ������� ������������ ������������� ����������
	NotNumberEntered,	// ���� ������������� �� �����
	IncorrectIdentifier,
	IncorrectExpression,
	NoError			
};

static const std::map<std::string, ErrorDescription> ERROR_DESCRIPRTION
{
	{ "Unknown command", ErrorDescription::UnknownCommand },
	{ "Invalid usage", ErrorDescription::InvalidUsage },
	{ "Name already exists", ErrorDescription::DuplicateName },
	{ "Name does not exist", ErrorDescription::NameNotExist },
	{ "Not a number entered", ErrorDescription::NotNumberEntered},
	{ "Incorrect identifier", ErrorDescription::IncorrectIdentifier },
	{ "Incorrect expression", ErrorDescription::IncorrectExpression }
};

class CCalculator
{
public:
	CCalculator() = default;

	bool DeclareVariable(const std::string& identifier);
	bool DeclareFunction(const std::string& identifier, std::string expression);

	

	bool IsOperandDeclared(const std::string& identifier) const;
	
	bool SetVariableValue(std::string identifier, std::string newValue);
	
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);
	std::optional<std::reference_wrapper<COperand>> GetOperandRef(const std::string& identifier) const;
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

private:
	bool ValidateIdentifier(const std::string& identifier);
	std::string RemoveAllSpaces(std::string str);


	std::vector<std::unique_ptr<COperand>> m_operands;  // std::unique_ptr �� ����� ������������ ������� - ����������� ����� ���������
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

// ��� ������ �������� � public
//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
//std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

//std::optional<std::unique_ptr<COperand>*> GetOperandRef(const std::string& identifier);
//std::optional<COperand*> GetOperandRef(const std::string& identifier) const;

//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
