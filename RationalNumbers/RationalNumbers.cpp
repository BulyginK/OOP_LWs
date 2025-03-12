#include "RationalNumbers.h"
#include <utility>
#include <stdexcept>

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
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalization();
};

void CRational::Normalization()
{
	const int gcd = GCD(m_numerator, m_denominator);
	if (gcd != 0) {
		m_numerator /= gcd;
		m_denominator /= gcd;
	}
};

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

int GCD(int a, int b)
{
	a = std::abs(a);
	b = std::abs(b);
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1; 
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
	return CRational(m_numerator, m_denominator);
}