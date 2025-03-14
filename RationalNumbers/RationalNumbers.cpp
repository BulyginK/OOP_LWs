#include "RationalNumbers.h"
#include <utility>
#include <stdexcept>

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational::CRational() : m_numerator(0), m_denominator(1) {};

CRational::CRational(int value) : m_numerator(value), m_denominator(1) {};

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator cannot be 0");
	}
	if (denominator < 0) // если знаменатель отрицателен - знак перемещают в числитель
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalization();
};

void CRational::Normalization()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
};

unsigned GCD(unsigned a, unsigned b) // Greates_Common_Divisor - НОД по алгоритму Евклида
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

unsigned LCM(unsigned a, unsigned b) // Least_Common_Multiple - НОК через НОД
{
	return (a * b) / GCD(a, b);
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
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

//CRational const CRational::operator-(const CRational& rhs)
//{
//	int lcm = LCM(m_numerator, rhs.GetDenominator());
//	int numerator = m_numerator * lcm / m_numerator
//		+ rhs.GetNumerator() * lcm / rhs.GetDenominator();
//	return CRational(numerator, lcm);
//}