#pragma once
#include <iostream>
#include <cmath>
#include <cfloat>

class CComplex
{
public:
    CComplex(double real = 0, double image = 0);
    double Re() const;               // ���������� �������������� ����� ������������ �����
    double Im() const;               // ���������� ������ ����� ������������ �����
    double GetMagnitude() const;     // ���������� ������ ������������ �����
    double GetArgument() const;      // ���������� �������� ������������ �����

    friend CComplex operator+(const CComplex& lhs, const CComplex& rhs); // friend �� operator+ � ��� ������� �������, � �� ����� � ��������� ������������ �������������� ��������
    friend CComplex operator-(const CComplex& lhs, const CComplex& rhs);
    friend CComplex operator*(const CComplex& lhs, const CComplex& rhs);
    friend CComplex operator/(const CComplex& lhs, const CComplex& rhs);

    // ������� ���������
    CComplex operator+() const;
    CComplex operator-() const;

    // ��������� ��������� ������������
    CComplex& operator+=(const CComplex& other);
    CComplex& operator-=(const CComplex& other);
    CComplex& operator*=(const CComplex& other);
    CComplex& operator/=(const CComplex& other);

    // ��������� ���������
    friend bool operator==(const CComplex& lhs, const CComplex& rhs);
    friend bool operator==(double lhs, const CComplex& rhs);
    friend bool operator!=(const CComplex& lhs, const CComplex& rhs);
    friend bool operator!=(double lhs, const CComplex& rhs);

    // ��������� �����/������
    friend std::ostream& operator<<(std::ostream& os, const CComplex& num);
    friend std::istream& operator>>(std::istream& is, CComplex& num);

private:
    double m_real;
    double m_image;
};

// ��������� �����/������
//std::ostream& operator<<(std::ostream& stream, const CComplex& num);
//std::istream& operator>>(std::istream& stream, CComplex& num);