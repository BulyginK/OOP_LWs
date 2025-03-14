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


	// ������������ ������������ �����, ������ ���� (0/1)
	// CRational();

	// ������������ ������������ �����, ������ value (value/1)
	// CRational(int value);

	// ������������ ������������ �����, ������ numerator/denominator
	// ������������ ����� ������ ��������� � ��������������� ����:
	// ����������� ������������� (��������� ����� ���� �������������)
	// ��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
	// ���� ����������� ����� ����, ������ ���������������� ������������ �����, ������ ����,
	// ���� ������ ���� ��������� ���������� std::invalid_argument.
	// CRational(int numerator, int denominator);