#include "stdafx.h"
#include "../LW5_ComplexNumbers/Complex.h"
#include <boost/optional.hpp>

void CheckingComplexNumber(const CComplex& compNum, double expectedReal, double expectedImage)
{
	BOOST_CHECK_EQUAL(compNum.Re(), expectedReal);
	BOOST_CHECK_EQUAL(compNum.Im(), expectedImage);
}

// проверка работы конструктора
BOOST_AUTO_TEST_SUITE(Checking_the_created_complex_number)
BOOST_AUTO_TEST_CASE(Constructor_tests)
{
	CheckingComplexNumber(CComplex(), 0, 0);
}
BOOST_AUTO_TEST_CASE(Real_number_constructor)
{
	CheckingComplexNumber(CComplex(5.0), 5.0, 0);
	CheckingComplexNumber(CComplex(-3.14), -3.14, 0);
}
BOOST_AUTO_TEST_CASE(Imaginary_number_constructor)
{
    CheckingComplexNumber(CComplex(0.0, 1.5), 0, 1.5);
    CheckingComplexNumber(CComplex(0.0, -2.0), 0, -2.0);
}
BOOST_AUTO_TEST_CASE(Full_complex_number_constructor)
{
    CheckingComplexNumber(CComplex(2.5, 3.7), 2.5, 3.7);
    CheckingComplexNumber(CComplex(-1.0, -4.2), -1.0, -4.2);
    CheckingComplexNumber(CComplex(0.5, -0.5), 0.5, -0.5);
}
BOOST_AUTO_TEST_CASE(NaN)
{
    BOOST_CHECK_THROW(CComplex(NAN, 0.0), std::invalid_argument);
    BOOST_CHECK_THROW(CComplex(0.0, NAN), std::invalid_argument);
    BOOST_CHECK_THROW(CComplex(NAN, NAN), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

// поверка получение действительной и мнимой частей
BOOST_AUTO_TEST_SUITE(Checking_complex_number_parts_access)
BOOST_AUTO_TEST_CASE(Re_method_tests)
{
    BOOST_CHECK_EQUAL(CComplex().Re(), 0.0);
    BOOST_CHECK_EQUAL(CComplex(3.14).Re(), 3.14);
    BOOST_CHECK_EQUAL(CComplex(-2.5).Re(), -2.5);
    BOOST_CHECK_EQUAL(CComplex(0.0, 5.0).Re(), 0.0);
    BOOST_CHECK_EQUAL(CComplex(1.5, -2.5).Re(), 1.5);
}
BOOST_AUTO_TEST_CASE(Im_method_tests)
{
    BOOST_CHECK_EQUAL(CComplex().Im(), 0.0);
    BOOST_CHECK_EQUAL(CComplex(3.14).Im(), 0.0);
    BOOST_CHECK_EQUAL(CComplex(0.0, 4.2).Im(), 4.2);
    BOOST_CHECK_EQUAL(CComplex(0.0, -1.0).Im(), -1.0);
    BOOST_CHECK_EQUAL(CComplex(1.5, -2.5).Im(), -2.5);
}
BOOST_AUTO_TEST_SUITE_END()

// проверка расчета модуля комплексного числа
BOOST_AUTO_TEST_SUITE(Checking_the_magnitude_of_complex_number)
BOOST_AUTO_TEST_CASE(Magnitude_of_zero_complex_number)
{
    CComplex num;
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 0.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_real_positive_number)
{
    CComplex num(3.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 3.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_real_negative_number)
{
    CComplex num(-4.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 4.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_imaginary_positive_number)
{
    CComplex num(0.0, 5.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 5.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_imaginary_negative_number)
{
    CComplex num(0.0, -12.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 12.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_complex_number_with_both_parts_positive)
{
    CComplex num(3.0, 4.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 5.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_complex_number_with_both_parts_negative)
{
    CComplex num(-6.0, -8.0);
    BOOST_CHECK_EQUAL(num.GetMagnitude(), 10.0);
}
BOOST_AUTO_TEST_CASE(Magnitude_of_complex_number_with_mixed_parts)
{
    CComplex num(1.0, -1.0);
    BOOST_CHECK_CLOSE_FRACTION(num.GetMagnitude(), std::sqrt(2.0), 1e-10);
}
BOOST_AUTO_TEST_SUITE_END()

// Проверка получения аргумента
BOOST_AUTO_TEST_SUITE(Checking_complex_number_argument)
BOOST_AUTO_TEST_CASE(Zero_complex_argument)
{
    CComplex num;
    BOOST_CHECK_THROW(num.GetArgument(), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(Positive_real_argument)
{
    CComplex num(5.0);
    BOOST_CHECK_EQUAL(num.GetArgument(), 0.0);
}
BOOST_AUTO_TEST_CASE(Negative_real_argument)
{
    CComplex num(-3.0);
    BOOST_CHECK_EQUAL(num.GetArgument(), M_PI);
}
BOOST_AUTO_TEST_CASE(Positive_imaginary_argument)
{
    CComplex num(0.0, 2.0);
    BOOST_CHECK_EQUAL(num.GetArgument(), M_PI_2);
}
BOOST_AUTO_TEST_CASE(Negative_imaginary_argument)
{
    CComplex num(0.0, -4.0);
    BOOST_CHECK_EQUAL(num.GetArgument(), -M_PI_2);
}
BOOST_AUTO_TEST_CASE(First_quadrant_argument)
{
    CComplex num(1.0, 1.0);
    BOOST_CHECK_CLOSE(num.GetArgument(), M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_CASE(Second_quadrant_argument)
{
    CComplex num(-1.0, 1.0);
    BOOST_CHECK_CLOSE(num.GetArgument(), 3 * M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_CASE(Third_quadrant_argument)
{
    CComplex num(-1.0, -1.0);
    BOOST_CHECK_CLOSE(num.GetArgument(), -3 * M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_CASE(Fourth_quadrant_argument)
{
    CComplex num(1.0, -1.0);
    BOOST_CHECK_CLOSE(num.GetArgument(), -M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_CASE(Small_values_argument)
{
    CComplex num(1e-20, 1e-20);
    BOOST_CHECK_CLOSE(num.GetArgument(), M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_CASE(Large_values_argument)
{
    CComplex num(1e20, 1e20);
    BOOST_CHECK_CLOSE(num.GetArgument(), M_PI / 4, 1e-10);
}
BOOST_AUTO_TEST_SUITE_END()

// сложение двух комплексных чисел - бинарынй плюс
BOOST_AUTO_TEST_SUITE(Complex_number_operator_banary_plus)
BOOST_AUTO_TEST_CASE(CComplex_plus_CComplex)
{
    CComplex a(1.5, 2.5);
    CComplex b(0.5, -1.5);
    CComplex result = a + b;
    CheckingComplexNumber(result, 2.0, 1.0);
}
BOOST_AUTO_TEST_CASE(CComplex_plus_double)
{
    CComplex a(1.0, 2.0);
    double b = 3.5;
    CComplex result = a + b;
    CheckingComplexNumber(result, 4.5, 2.0);
}
BOOST_AUTO_TEST_CASE(double_plus_CComplex)
{
    double a = 2.0;
    CComplex b(-1.0, 3.0);
    CComplex result = a + b;
    CheckingComplexNumber(result, 1.0, 3.0);
}
BOOST_AUTO_TEST_CASE(double_plus_double)
{
    double a = 2.0;
    double b = 3.0;
    CComplex result = a + b;
    CheckingComplexNumber(result, 5.0, 0.0);
}
BOOST_AUTO_TEST_CASE(Mixed_addition)
{
    CComplex a(1.0, 1.0);
    double b = 2.0;
    CComplex c(0.5, -1.0);
    CComplex result1 = (a + b) + c;
    CComplex result2 = a + (b + c);
    CheckingComplexNumber(result1, 3.5, 0.0);
    CheckingComplexNumber(result2, 3.5, 0.0);
}
BOOST_AUTO_TEST_SUITE_END()

// разница двух комплексных чисел - бинарынй минус
BOOST_AUTO_TEST_SUITE(Complex_number_operator_banary_minus)
BOOST_AUTO_TEST_CASE(CComplex_minus_CComplex)
{
    CComplex a(1.5, 2.5);
    CComplex b(0.5, -1.5);
    CComplex result = a - b;
    CheckingComplexNumber(result, 1.0, 4.0);
}
BOOST_AUTO_TEST_CASE(CComplex_minus_double)
{
    CComplex a(1.0, 2.0);
    double b = 3.5;
    CComplex result = a - b;
    CheckingComplexNumber(result, -2.5, 2.0);
}
BOOST_AUTO_TEST_CASE(double_minus_CComplex)
{
    double a = 2.0;
    CComplex b(-1.5, 3.0);
    CComplex result = a - b;
    CheckingComplexNumber(result, 3.5, -3.0);
}
BOOST_AUTO_TEST_CASE(double_minus_double)
{
    double a = -2.0;
    double b = 3.5;
    CComplex result = a - b;
    CheckingComplexNumber(result, -5.5, 0.0);
}
BOOST_AUTO_TEST_CASE(Mixed_difference)
{
    CComplex a(1.0, 1.0);
    double b = 2.0;
    CComplex c(0.5, -1.0);
    CComplex result1 = (a - b) - c;
    CComplex result2 = a - (b - c);
    CheckingComplexNumber(result1, -1.5, 2.0);
    CheckingComplexNumber(result2, -0.5, 0.0);
}
BOOST_AUTO_TEST_SUITE_END()

// умножение двух комплексных чисел
BOOST_AUTO_TEST_SUITE(Multiplication_operator)
BOOST_AUTO_TEST_CASE(CComplex_multiply_CComplex)
{
    CComplex a(1.0, 2.0);
    CComplex b(3.0, 4.0);
    CComplex result = a * b;
    // (1*3 - 2*4) + (1*4 + 2*3)i = -5 + 10i
    CheckingComplexNumber(result, -5.0, 10.0);
}
BOOST_AUTO_TEST_CASE(double_multiply_CComplex)
{
    double a = 2.0;
    CComplex b(-1.0, 3.0);
    CComplex result = a * b;
    CheckingComplexNumber(result, -2.0, 6.0); // (2.0*-1.0) + (2.0*3.0)i
}
BOOST_AUTO_TEST_SUITE_END()

// деление двух комплексных чисел
BOOST_AUTO_TEST_SUITE(Division_operator)
BOOST_AUTO_TEST_CASE(CComplex_divide_CComplex)
{
    CComplex a(4.0, 4.0);
    CComplex b(2.0, -2.0);
    CComplex result = a / b;
    // (4*2 + 4*(-2))/(4+4) + (4*2 - 4*(-2))/(4+4)i = 0 + 2i
    CheckingComplexNumber(result, 0.0, 2.0);
}
BOOST_AUTO_TEST_CASE(double_divide_CComplex)
{
    double a = 6.0;
    CComplex b(3.0, 0.0);
    CComplex result = a / b;
    CheckingComplexNumber(result, 2.0, 0.0);
}
BOOST_AUTO_TEST_CASE(Division_by_zero)
{
    CComplex a(1.0, 1.0);
    CComplex zero;
    BOOST_CHECK_THROW(a / zero, std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Comparison_operators)
BOOST_AUTO_TEST_CASE(Equality_operator)
{
    CComplex a(1.23456789, 9.87654321);
    CComplex b(1.23456789, 9.87654321);
    BOOST_CHECK(a == b);
}
BOOST_AUTO_TEST_CASE(Inequality_operator)
{
    CComplex a(1.0, 2.0);
    CComplex b(1.0, 2.1);
    BOOST_CHECK(a != b);
}
BOOST_AUTO_TEST_CASE(Compare_with_double)
{
    CComplex a(3.0, 0.0);
    double b = 3.0;
    BOOST_CHECK(a == b);
}
BOOST_AUTO_TEST_SUITE_END()

// Операторы составного присваивания
BOOST_AUTO_TEST_SUITE(Compound_assignment_operators)
BOOST_AUTO_TEST_CASE(Plus_equals_operator)
{
    CComplex a(1.5, 2.5);
    const CComplex b(0.5, -1.5);
    a += b;
    CheckingComplexNumber(a, 2.0, 1.0);

    CComplex c(1.0, 2.0);
    c += 3.5;
    CheckingComplexNumber(c, 4.5, 2.0);
}
BOOST_AUTO_TEST_CASE(Minus_equals_operator)
{
    CComplex a(3.0, 4.0);
    const CComplex b(1.0, 2.0);
    a -= b;
    CheckingComplexNumber(a, 2.0, 2.0);

    CComplex c(5.0, 1.0);
    c -= 2.0;
    CheckingComplexNumber(c, 3.0, 1.0);
}
BOOST_AUTO_TEST_CASE(Multiply_equals_operator)
{
    CComplex a(1.0, 2.0);
    const CComplex b(3.0, 4.0);
    a *= b;
    // (1*3 - 2*4) + (1*4 + 2*3)i = -5 + 10i
    CheckingComplexNumber(a, -5.0, 10.0);

    CComplex c(2.0, 3.0);
    c *= 1.5;
    CheckingComplexNumber(c, 3.0, 4.5);
}
BOOST_AUTO_TEST_CASE(Divide_equals_operator)
{
    CComplex a(4.0, 4.0);
    const CComplex b(2.0, -2.0);
    a /= b;
    // (4*2 + 4*(-2))/(4+4) + (4*2 - 4*(-2))/(4+4)i = 0 + 2i
    CheckingComplexNumber(a, 0.0, 2.0);

    CComplex c(6.0, 3.0);
    c /= 3.0;
    CheckingComplexNumber(c, 2.0, 1.0);

    // Проверка деления на ноль
    CComplex d(1.0, 1.0);
    CComplex zero;
    BOOST_CHECK_THROW(d /= zero, std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(Compound_operators_chaining)
{
    CComplex a(1.0, 2.0);
    const CComplex b(0.5, -1.0);

    // Проверка цепочки операторов
    (((a += b) -= CComplex(0.2, 0.0)) *= 2.0) /= CComplex(1.0, 0.0);

    // ((1.0+0.5) + (2.0-1.0)i) = 1.5 + 1.0i
    // (1.5-0.2) + 1.0i = 1.3 + 1.0i
    // (1.3*2.0) + (1.0*2.0)i = 2.6 + 2.0i
    // (2.6/1.0) + (2.0/1.0)i = 2.6 + 2.0i
    CheckingComplexNumber(a, 2.6, 2.0);
}
BOOST_AUTO_TEST_SUITE_END()

// оператора вывода и вывода
BOOST_AUTO_TEST_SUITE(Input_output_operators)
BOOST_AUTO_TEST_CASE(Output_operator)
{
    std::ostringstream output;

    output << CComplex(3.5, 4.2);
    BOOST_CHECK_EQUAL(output.str(), "3.5+4.2i");
    output.str("");

    output << CComplex(1.0, -2.0);
    BOOST_CHECK_EQUAL(output.str(), "1-2i");
    output.str("");

    output << CComplex(-3.0, 0.0);
    BOOST_CHECK_EQUAL(output.str(), "-3+0i");
    output.str("");

    output << CComplex();
    BOOST_CHECK_EQUAL(output.str(), "0+0i");
    output.str("");

    output << CComplex(0.0, 1.5);
    BOOST_CHECK_EQUAL(output.str(), "0+1.5i");
}

BOOST_AUTO_TEST_CASE(Input_operator_valid)
{
    std::istringstream input;
    
    CComplex num1;
    input.str("-3.5-4.8i");
    input >> num1;
    BOOST_CHECK_EQUAL(num1.Re(), -3.5);
    BOOST_CHECK_EQUAL(num1.Im(), -4.8);

    CComplex num2;
    //input.clear();
    input.str("4+2i");
    input >> num2;
    BOOST_CHECK_EQUAL(num2.Re(), 4.0);
    BOOST_CHECK_EQUAL(num2.Im(), 2.0);

    CComplex num3;
    //input.clear();
    input.str("-3+2i");
    input >> num3;
    BOOST_CHECK_EQUAL(num3.Re(), -3.0);
    BOOST_CHECK_EQUAL(num3.Im(), 2.0);

    CComplex num4;
    //input.clear();
    input.str("3-2i");
    input >> num4;
    BOOST_CHECK_EQUAL(num4.Re(), 3.0);
    BOOST_CHECK_EQUAL(num4.Im(), -2.0);

    CComplex num5;
    input.str("0-0i");
    input >> num5;
    BOOST_CHECK_EQUAL(num5.Re(), 0.0);
    BOOST_CHECK_EQUAL(num5.Im(), 0.0);
}

BOOST_AUTO_TEST_CASE(Input_operator_invalid)
{
    std::istringstream input;
    CComplex num;

    input.str("1+2");
    input >> num;
    BOOST_CHECK(input.fail());

    input.clear();
    input.str("abc+2i");
    input >> num;
    BOOST_CHECK(input.fail());

    input.clear();
    input.str("");
    input >> num;
    BOOST_CHECK(input.fail());
}

// Проверяем, что получили исходное число
BOOST_AUTO_TEST_CASE(Input_output_roundtrip)
{
    const CComplex original(1.23, -4.56);
    std::stringstream ss;

    ss << original;

    CComplex readBack;
    ss >> readBack;

    BOOST_CHECK_EQUAL(original.Re(), readBack.Re());
    BOOST_CHECK_EQUAL(original.Im(), readBack.Im());
}

BOOST_AUTO_TEST_SUITE_END()