#pragma once
#include <stdexcept>

// CUrlParsingError ����������� �� std::invalid_argument
// std::invalid_argument � ��� ����������� ����� ����������
class CUrlParsingError : public std::invalid_argument  // �������, � ���� �������, �������������� std::logic_error
{
public:
    CUrlParsingError(const std::string& message);
};