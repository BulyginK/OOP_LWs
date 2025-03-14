#pragma once
#include <sstream>
//#include <cmath>

class CRational final
{
public:
	CRational(int num = 0, int denom = 1);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	CRational const operator-() const;
	CRational const operator+() const;

	CRational& operator+=(const CRational& rhs);
	CRational& operator-=(const CRational& rhs);
	CRational& operator*=(const CRational& rhs);
	CRational& operator/=(const CRational& rhs);

	std::pair<int, CRational> ToCompoundFraction() const;

private:
	int m_num;
	int m_denom;

	void Normalization();
};

unsigned GCD(unsigned a, unsigned b);
unsigned LCM(unsigned a, unsigned b);

CRational const operator+(const CRational& lhs, const CRational& rhs);
CRational const operator-(const CRational& lhs, const CRational& rhs);
CRational const operator*(const CRational& lhs, const CRational& rhs);
CRational const operator/(const CRational& lhs, const CRational& rhs);

bool const operator==(const CRational& lhs, const CRational& rhs);
bool const operator!=(const CRational& lhs, const CRational& rhs);

bool const operator<(const CRational& lhs, const CRational& rhs);
bool const operator<=(const CRational& lhs, const CRational& rhs);
bool const operator>(const CRational& lhs, const CRational& rhs);
bool const operator>=(const CRational& lhs, const CRational& rhs);

std::ostream& operator<<(std::ostream& strm, const CRational& rhs);
std::istream& operator>>(std::istream& strm, CRational& rhs);