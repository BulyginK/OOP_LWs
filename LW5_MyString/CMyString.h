#pragma once
#include <string>

class CMyString
{
public:
    // ����������� �� ���������
    CMyString();

    // �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
    CMyString(const char * pString);

    // �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
    CMyString(const char * pString, size_t length);

    // ����������� �����������
    CMyString(CMyString const& other);

    // ������������ �����������
    // ����������� ��������� � ������������ ���������� ������������ 
    CMyString(CMyString&& other) noexcept;

    // �����������, ���������������� ������ ������� �� 
    // ������ ����������� ���������� C++
    CMyString(std::string const& stlString);

    // ���������� ������ - ����������� ������, ���������� ��������� ������
    ~CMyString();

    // ���������� ����� ������ (��� ����� ������������ �������� �������)
    size_t GetLength() const;

    // ���������� ��������� �� ������ �������� ������.
    // � ����� ������� ����������� ������ ���� ����������� ������� ������
    // ���� ���� ������ ������ 
    const char* GetStringData() const;

    // ���������� ��������� � �������� ������� ������ �� ������ length ��������
    CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    // ������� ������ (������ ���������� ����� ������� �����)
    void Clear();

    // ���������� ����������� ������
    size_t GetCapacity() const;
private:
    CMyString(const char* pString, size_t length, bool copyData);

    static char s_emptyString;
    char* m_pString; // m_pString ����� ��� char* (������������� ���������).
    size_t m_length;
    size_t m_capacity;
};

bool operator ==(const CMyString& lhs, const CMyString& rhs);
