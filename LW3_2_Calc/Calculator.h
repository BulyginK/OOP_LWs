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
	IncorrectIdentifier,
	IncorrectExpression,
	NoError			
};

class CCalculator
{
public:
	CCalculator() = default;

	bool DeclareVariable(const std::string& identifier);
	bool DeclareFunction(const std::string& identifier, std::string expression);

	bool IsOperandDeclared(const std::string& identifier) const;
	bool SetVariableValue(std::string identifier, std::string newValue);
	std::map<std::string, double> GetAllOperands() const;
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);

	std::optional<std::reference_wrapper<COperand>> GetOperandRef(const std::string& identifier) const;

	std::optional<double> CountValue(const std::string& identifier);
	double Calculate(const std::string& identifier, double& res);

	static std::string RemoveAllSpaces(std::string str);

private:
	bool ValidateIdentifier(const std::string& identifier);
	bool GetOperandFunctionExpression(const std::string& identifier, const std::string& exprNoSpaces);

	std::vector<std::unique_ptr<COperand>> m_operands;  // std::unique_ptr �� ����� ������������ ������� - ����������� ����� ���������
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};
