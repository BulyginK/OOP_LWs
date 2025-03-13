#pragma once

class CRational final
{
public:
    // ������������ ������������ �����, ������ ���� (0/1)
    CRational();

    // ������������ ������������ �����, ������ value (value/1)
    CRational(int value);

    // ������������ ������������ �����, ������ numerator/denominator
    // ������������ ����� ������ ��������� � ��������������� ����:
    // ����������� ������������� (��������� ����� ���� �������������)
    // ��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
    // ���� ����������� ����� ����, ������ ���������������� ������������ �����, ������ ����,
    // ���� ������ ���� ��������� ���������� std::invalid_argument.
    CRational(int numerator, int denominator);

    // ���������� ���������
    int GetNumerator() const;

    // ���������� ����������� (����������� �����)
    int GetDenominator() const;

    // ���������� ��������� ��������� � ����������� � ���� ����� double
    double ToDouble() const;

    // ������ ��������� �������� �������
	CRational const operator-() const;
	CRational const operator+() const;

private:
    int m_numerator;
    int m_denominator;

    void Normalization();
};

unsigned GCD(unsigned a, unsigned b);
unsigned LCM(unsigned a, unsigned b);

CRational const operator+(const CRational& lhs, const CRational& rhs);
CRational const operator-(const CRational& lhs, const CRational& rhs);
//lhs � ���������� �� Left Hand Side(����� �������).
//rhs � ���������� �� Right Hand Side (������ �������).