#include "CMyString.h"

char CMyString::m_emptyString = '\0';

// pString объ€влен как const char* (указатель на константные данные)
CMyString::CMyString(const char* pString, size_t length, bool copyData) 
	: m_length(length)
	, m_capacity(length)
{
	// указать какие конструкторы при том или ином условии
	if (m_length > 0 && copyData)
	{
		m_pString = new char[m_length + 1];
		memcpy(m_pString, pString, m_length);
		m_pString[m_length] = '\0';
	}
	else if (pString != nullptr && !copyData)
	{
		m_pString = const_cast<char*>(pString); // m_pString имеет тип char* (неконстантный указатель).
		//const_cast снимает константность, позвол€€ присвоить const char* переменной char*.
	}
	else
	{
		m_pString = &m_emptyString;
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

// ¬ зависимости от контекста вызова, компил€тор будет :
//  опировать аргумент(если передаЄтс€ lvalue) - вызовет конструктор копировани€.
// ѕеремещать аргумент(если передаЄтс€ rvalue) - вызовет перемещающий конструктор.

// конструктор копировани€
CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_pString, other.m_length, true)
{
}

// перемещающий конструктор
// CMyString&& other - cсылка на временный объект

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other.m_pString, other.m_length, false)
{
	other.m_pString = &m_emptyString;
	other.m_length = 0;
	other.m_capacity = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.data(), stlString.length(), true)
	// stlString.data() возвращает указатель на внутренний массив символов строки
	// stlString.length() возвращает длину строки (без нуль-терминатора)
	// true указывает, что данные нужно скопировать (так как std::string может изменитьс€ или быть уничтожена)
{
}

CMyString::~CMyString()
{
	if (m_pString != &m_emptyString) {
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



// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length || m_pString == &m_emptyString)
	{
		return CMyString();
	}
	size_t availableLength = m_length - start; // ¬ычисл€ем доступную длину от start до конца строки
	//  орректируем length, если он превышает доступную длину или равен SIZE_MAX
	size_t actualLength = (length == SIZE_MAX || length > availableLength)
		? availableLength
		: length;

	return CMyString(m_pString + start, actualLength);
}

void CMyString::Clear()
{
	if (m_pString != &m_emptyString)
	{
		delete[] m_pString;
	}
	m_pString = &m_emptyString;
	m_length = 0;
	m_capacity = 0;
}

void CMyString::Swap(CMyString& src) noexcept
{
	std::swap(m_pString, src.m_pString);
	std::swap(m_length, src.m_length);
	std::swap(m_capacity, src.m_capacity);
};

// ѕринимает параметр по значению (автоматически создаЄтс€ копи€ или перемещаетс€ временный объект).
CMyString& CMyString::operator=(CMyString other) { 
	Swap(other);
	return *this;
}

bool operator==(const CMyString& lhs, const CMyString& rhs) {
	return lhs.GetLength() == rhs.GetLength()
		&& memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength() + 1) == 0;
}

CMyString operator+(const CMyString& lhs, const CMyString& rhs) 
{
	if (lhs.GetLength() == 0 && rhs.GetLength() == 0)
	{
		return CMyString();
	}


	size_t newLength = lhs.GetLength() + rhs.GetLength();

	m_pString[m_length] = '\0';

	return CMyString();
}

// ѕерегрузка операторов
// habr.com/ru/articles/489666/
// 
// Ќачально разработанные конструторы
/*
CMyString::CMyString()
	: m_pString(&s_emptyString) // &s_emptyString возвращает указатель на единственный s_emptyString в куче (чтобы не плодить лишние '\0)
	, m_length(0)
	, m_capacity(0)
{
};

CMyString::CMyString(const char* pString) // ѕринимает const char* pString Ч указатель на строку в стиле C (завершающуюс€ нуль-терминатором \0).
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