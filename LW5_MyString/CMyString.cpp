#include "CMyString.h"

char CMyString::s_emptyString = '\0';

// pString �������� ��� const char* (��������� �� ����������� ������)
CMyString::CMyString(const char* pString, size_t length, bool copyData) 
	: m_length(length)
	, m_capacity(length)
{
	if (m_length > 0 && copyData)
	{
		m_pString = new char[m_length + 1];
		memcpy(m_pString, pString, m_length);
		m_pString[m_length] = '\0';
	}
	else if (pString != nullptr && !copyData)
	{
		m_pString = const_cast<char*>(pString); // m_pString ����� ��� char* (������������� ���������).
		//const_cast ������� �������������, �������� ��������� const char* ���������� char*.
	}
	else
	{
		m_pString = &s_emptyString;
		m_capacity = 0;
	}
}

CMyString::CMyString()
	: CMyString(nullptr, 0, false)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, pString ? strlen(pString) : 0, true)
{
}

CMyString::CMyString(const char* pString, size_t length)
	: CMyString(pString, length, true)
{
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_pString, other.m_length, true)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other.m_pString, other.m_length, false)
{
	other.m_pString = &s_emptyString;
	other.m_length = 0;
	other.m_capacity = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.data(), stlString.length(), true)
	// stlString.data() ���������� ��������� �� ���������� ������ �������� ������
	// stlString.length() ���������� ����� ������ (��� ����-�����������)
	// true ���������, ��� ������ ����� ����������� (��� ��� std::string ����� ���������� ��� ���� ����������)
{
}

CMyString::~CMyString()
{
	if (m_pString != &s_emptyString) {
		delete[] m_pString;
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

char const* CMyString::GetStringData() const
{
	return m_pString;
}

bool operator==(const CMyString& lhs, const CMyString& rhs) {
	return lhs.GetLength() == rhs.GetLength()
		&& memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength() + 1) == 0;
}

// ���������� ��������� � �������� ������� ������ �� ������ length ��������
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length || m_pString == &s_emptyString)
	{
		return CMyString();
	}
	size_t availableLength = m_length - start; // ��������� ��������� ����� �� start �� ����� ������
	// ������������ length, ���� �� ��������� ��������� ����� ��� ����� SIZE_MAX
	size_t actualLength = (length == SIZE_MAX || length > availableLength)
		? availableLength
		: length;

	return CMyString(m_pString + start, actualLength);
}

void CMyString::Clear()
{
	if (m_pString != &s_emptyString)
	{
		delete[] m_pString;
	}
	m_pString = &s_emptyString;
	m_length = 0;
	m_capacity = 0;
}

// �������� ������������� �����������
/*
CMyString::CMyString()
	: m_pString(&s_emptyString) // &s_emptyString ���������� ��������� �� ������������ s_emptyString � ���� (����� �� ������� ������ '\0)
	, m_length(0)
	, m_capacity(0)
{
};

CMyString::CMyString(const char* pString) // ��������� const char* pString � ��������� �� ������ � ����� C (������������� ����-������������ \0).
	: m_length(pString ? strlen(pString) : 0)
{
	if (m_length > 0)
	{
		m_pString = new char[m_length + 1];
		memcpy(m_pString, pString, m_length + 1);
		m_capacity = m_length;
	}
	else
	{
		m_pString = &s_emptyString;
		m_capacity = 0;
	}
};

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	if (length > 0)
	{
		m_pString = new char[length + 1];
		memcpy(m_pString, pString, length);
		m_pString[length] = '\0';
		m_capacity = length;
	}
	else
	{
		m_pString = &s_emptyString;
		m_capacity = 0;
	}
}

CMyString::CMyString(CMyString const& other)
	: m_length(other.m_length)
{
	if (m_length > 0)
	{
		m_pString = new char[m_length + 1];
		memcpy(m_pString, other.m_pString, m_length + 1);
		m_capacity = m_length;
	}
	else
	{
		m_pString = &s_emptyString;
		m_capacity = 0;
	}
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_pString(other.m_pString)
	, m_length(other.m_length)
	, m_capacity(other.m_capacity)
{
	other.m_pString = &s_emptyString;
	other.m_length = 0;
	other.m_capacity = 0;
}*/