#include "RationalNumbers.h"
#include <utility>
#include <stdexcept>

//#include <cassert>

CRational::CRational(int num, int denom)
	: m_num(num)
	, m_denom(denom)
{
	if (denom == 0)
	{
		throw std::invalid_argument("Denominator cannot be 0");
	}
	if (denom < 0)
	{
		m_num = -m_num;
		m_denom = -m_denom;
	}
	Normalization();
};

int CRational::GetNumerator() const
{
	return m_num;
}

int CRational::GetDenominator() const
{
	return m_denom;
}


void CRational::Normalization()
{
	const int gcd = GCD(abs(m_num), m_denom);
	if (gcd != 0) {
		m_num /= gcd;
		m_denom /= gcd;
	}
};

// Greates_Common_Divisor - НОД по алгоритму Евклида
unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

// Least_Common_Multiple - НОК через НОД
unsigned LCM(unsigned a, unsigned b)
{
	return (a * b) / GCD(a, b);
}
// Реализация метода ToDouble()
double CRational::ToDouble() const
{
	return static_cast<double>(m_num) / m_denom;
}
// Реализация унарного плюса и унарного минуса
CRational const CRational::operator-() const
{
	return CRational(-m_num, m_denom);
}
CRational const CRational::operator+() const
{
	return *this; // Разыменование this
}
// Реализация бинарного +
CRational const operator+(const CRational& lhs, const CRational& rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lhs.GetNumerator() * lcm / lhs.GetDenominator()
		+ rhs.GetNumerator() * lcm / rhs.GetDenominator();
	return CRational(numerator, lcm);
}
// Реализация бинарного -
CRational const operator-(const CRational& lhs, const CRational& rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lhs.GetNumerator() * lcm / lhs.GetDenominator()
		- rhs.GetNumerator() * lcm / rhs.GetDenominator();
	return CRational(numerator, lcm);
}
// Реализация +=
CRational& CRational::operator+=(const CRational& rhs)
{
	*this = *this + rhs;
	return *this;
}
// Реализация -=
CRational& CRational::operator-=(CRational const& rhs)
{
	*this = *this - rhs;
	return *this;
}
// Реализация *
CRational const operator*(const CRational& lhs, const CRational& rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator()));
}
// Реализация /
CRational const operator/(const CRational& lhs, const CRational& rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator()));
}
// Реализация *= 
CRational& CRational::operator *=(const CRational& rhs)
{
	m_num *= rhs.GetNumerator();
	m_denom *= rhs.GetDenominator();
	Normalization();
	return *this;
}
// Реализация /= 
CRational& CRational::operator /=(const CRational& rhs)
{
	if (rhs.GetNumerator() == 0)
	{
		throw std::invalid_argument("Denominator cannot be 0");
	}
	m_num *= rhs.GetDenominator();
	m_denom *= rhs.GetNumerator();
	Normalization();
	return *this;
}
// Реализация == и !=
bool const operator==(const CRational& lhs, const CRational& rhs)
{
	return (lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator());
}

bool const operator!=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs == rhs);
}
// Реализация <, >, <=, >=
bool const operator<(const CRational& lhs, const CRational& rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator());
}
bool const operator<=(const CRational& lhs, const CRational& rhs)
{
	return (lhs == rhs || lhs < rhs);
}
bool const operator>(const CRational& lhs, const CRational& rational2)
{
	return !(lhs <= rational2);
}
bool const operator>=(const CRational& lhs, const CRational& rhs)
{
	return (lhs == rhs || lhs > rhs);
}
// Реализация вывода рационального числа в выходной поток
std::ostream& operator<<(std::ostream& strm, const CRational& rhs)
{
	strm << rhs.GetNumerator() << '/' << rhs.GetDenominator();
	return strm;
}
// Реализация ввода рационального числа из входного потока
std::istream& operator>>(std::istream& strm, CRational& rhs)
{
	int numerator;
	int denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rhs = CRational(numerator, denominator);
	}
	else
	{
		strm.setstate(std::ios_base::failbit); // установлен флаг ошибки
	}
	return strm;
}
// Реализация возможности получения смешанной дроби из рационального числа
std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	int integer = static_cast<int>(ToDouble());
	int numerator = m_num - m_denom * integer;
	return std::make_pair(std::move(integer), CRational(numerator, m_denom));
}