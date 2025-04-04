#pragma once
#include <stdexcept>

// CUrlParsingError ����������� �� std::invalid_argument
// std::invalid_argument � ��� ����������� ����� ����������
// �������, � ���� �������, �������������� std::logic_error
class CUrlParsingError : public std::invalid_argument  
{
public:
    CUrlParsingError(const std::string& message);
};