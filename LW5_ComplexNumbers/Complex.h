#pragma once
#include <iostream>
#include <cmath>
#include <cfloat>

class CComplex
{
public:
    CComplex(double real = 0, double image = 0);
    double Re() const;               // возвращает действительную часть комплексного числа
    double Im() const;               // возвращает мнимую часть комплексного числа
    double GetMagnitude() const;     // возвращает модуль комплексного числа
    double GetArgument() const;      // возвращает аргумент комплексного числа

    friend CComplex operator+(const CComplex& lhs, const CComplex& rhs); // friend тк operator+ Ч это внешн€€ функци€, а не метод и позвол€ет использовать симметричность операций
    friend CComplex operator-(const CComplex& lhs, const CComplex& rhs);
    friend CComplex operator*(const CComplex& lhs, const CComplex& rhs);
    friend CComplex operator/(const CComplex& lhs, const CComplex& rhs);

    // ”нарные операторы
    CComplex operator+() const;
    CComplex operator-() const;

    // —оставные операторы присваивани€
    CComplex& operator+=(const CComplex& other);
    CComplex& operator-=(const CComplex& other);
    CComplex& operator*=(const CComplex& other);
    CComplex& operator/=(const CComplex& other);

    // ќператоры сравнени€
    friend bool operator==(const CComplex& lhs, const CComplex& rhs);
    friend bool operator==(double lhs, const CComplex& rhs);
    friend bool operator!=(const CComplex& lhs, const CComplex& rhs);
    friend bool operator!=(double lhs, const CComplex& rhs);

    // ќператоры ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const CComplex& num);
    friend std::istream& operator>>(std::istream& is, CComplex& num);

private:
    double m_real;
    double m_image;
};

// ќператоры ввода/вывода
//std::ostream& operator<<(std::ostream& stream, const CComplex& num);
//std::istream& operator>>(std::istream& stream, CComplex& num);