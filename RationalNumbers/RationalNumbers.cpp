#include "RationalNumbers.h"
#include <utility>
#include <stdexcept>

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

double CRational::ToDouble() const
{
	return static_cast<double>(m_num) / m_denom;
}

CRational const CRational::operator-() const
{
	return CRational(-m_num, m_denom);
}

CRational const CRational::operator+() const
{
	return *this; // Разыменование this
}

CRational const operator+(const CRational& lhs, const CRational& rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lhs.GetNumerator() * lcm / lhs.GetDenominator()
		+ rhs.GetNumerator() * lcm / rhs.GetDenominator();
	return CRational(numerator, lcm);
}

CRational const operator-(const CRational& lhs, const CRational& rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lhs.GetNumerator() * lcm / lhs.GetDenominator()
		- rhs.GetNumerator() * lcm / rhs.GetDenominator();
	return CRational(numerator, lcm);
}


//CRational::CRational() : m_numerator(0), m_denominator(1) {};
//
//CRational::CRational(int value) : m_numerator(value), m_denominator(1) {};
//
//CRational::CRational(int numerator, int denominator)
//	: m_numerator(numerator)
//	, m_denominator(denominator)
//{
//	if (denominator == 0)
//	{
//		throw std::invalid_argument("Denominator cannot be 0");
//	}
//	if (denominator < 0) // если знаменатель отрицателен - знак перемещают в числитель
//	{
//		m_numerator = -m_numerator;
//		m_denominator = -m_denominator;
//	}
//	Normalization();
//};