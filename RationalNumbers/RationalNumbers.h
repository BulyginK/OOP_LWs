#pragma once

class CRational
{
public:
	CRational(int num = 0, int denom = 1);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	CRational const operator-() const;
	CRational const operator+() const;

	//CRational const operator-(const CRational& rhs);

private:
	int m_num = 0;
	int m_denom = 1;

	void Normalization();
};

unsigned GCD(unsigned a, unsigned b);
unsigned LCM(unsigned a, unsigned b);

CRational const operator+(const CRational& lhs, const CRational& rhs);
CRational const operator-(const CRational& lhs, const CRational& rhs);


	//  онструирует рациональное число, равное нулю (0/1)
	// CRational();

	//  онструирует рациональное число, равное value (value/1)
	// CRational(int value);

	//  онструирует рациональное число, равное numerator/denominator
	// –ациональное число должно хранитьс€ в нормализованном виде:
	// знаменатель положительный (числитель может быть отрицательным)
	// числитель и знаменатель не имеют общих делителей (6/8 => 3/4 и т.п.)
	// ≈сли знаменатель равен нулю, должно конструироватьс€ рациональное число, равное нулю,
	// либо должно быть выброшено исключение std::invalid_argument.
	// CRational(int numerator, int denominator);