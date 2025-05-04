#pragma once

class CComplex
{
public:
    CComplex(double real = 0, double image = 0);
    double Re() const;               // возвращает действительную часть комплексного числа
    double Im() const;               // возвращает мнимую часть комплексного числа
    double GetMagnitude() const;     // возвращает модуль комплексного числа
    double GetArgument() const;      // возвращает аргумент комплексного числа


private:
    double m_real;
    double m_image;
};