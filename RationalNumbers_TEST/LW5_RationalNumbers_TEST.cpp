#include "stdafx.h"
#include "../RationalNumbers/RationalNumbers.h"

void CheckingRationalNumber(const CRational& rational, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rational.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(rational.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Checking_the_created_rational_number)
// Конструируется рациональное число, равное нулю (0/1)
BOOST_AUTO_TEST_CASE(Constructor_without_parameters)
{
	CheckingRationalNumber(CRational(), 0, 1);
}
// Конструируется рациональное число, равное value (value/1)
BOOST_AUTO_TEST_CASE(Constructor_with_one_parameter)
{
	CheckingRationalNumber(CRational(10), 10, 1);
	CheckingRationalNumber(CRational(-10), -10, 1);
	CheckingRationalNumber(CRational(0), 0, 1);
	CheckingRationalNumber(CRational(1), 1, 1);
	CheckingRationalNumber(CRational(10.56), 10, 1);
}
// Проверка определения НОД
BOOST_AUTO_TEST_CASE(Test_Greates_Common_Divisor)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1);
	BOOST_CHECK_EQUAL(GCD(7, 7), 7);
	BOOST_CHECK_EQUAL(GCD(1, 10), 1);
	BOOST_CHECK_EQUAL(GCD(10, 1), 1);
	BOOST_CHECK_EQUAL(GCD(655360001, 562448657), 1);
	BOOST_CHECK_EQUAL(GCD(123456789, 987654321), 9);
}
// Конструируется рациональное число, равное numerator/denominator
BOOST_AUTO_TEST_CASE(Constructor_with_two_parameters)
{
	CheckingRationalNumber(CRational(2, 3), 2, 3);
	CheckingRationalNumber(CRational(5, 1), 5, 1);
	CheckingRationalNumber(CRational(5, -1), -5, 1); // знаменатель положительный, числитель может быть отрицательным
	CheckingRationalNumber(CRational(-5, -1), 5, 1);
	CheckingRationalNumber(CRational(6, 8), 3, 4);
	CheckingRationalNumber(CRational(6, -8), -3, 4);
	CheckingRationalNumber(CRational(-6, 8), -3, 4);
	CheckingRationalNumber(CRational(-6, -8), 3, 4);
	CheckingRationalNumber(CRational(-10, 20), -1, 2);
}
// Знаменатель равен 0 - должно быть выброшено исключение
BOOST_AUTO_TEST_CASE(Denominator_is_0)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(-1, 0), std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(0, 0), std::invalid_argument);
}
// Реализация метода ToDouble() - Возвращает отношение числителя и знаменателя в виде числа double
BOOST_AUTO_TEST_CASE(Implementation_of_the_ToDouble_method)
{
	BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
	BOOST_CHECK_EQUAL(CRational(10, 4).ToDouble(), 2.5);
	BOOST_CHECK_EQUAL(CRational(-3, 4).ToDouble(), -0.75);
	BOOST_CHECK_EQUAL(CRational(-10, -4).ToDouble(), 2.5);
	BOOST_CHECK_EQUAL(CRational(0, 10).ToDouble(), 0.0);
	BOOST_CHECK_EQUAL(CRational(7, 7).ToDouble(), 1.0);
	BOOST_REQUIRE_THROW(CRational(10, 0).ToDouble(), std::invalid_argument);
}
// Реализация унарного плюса и унарного минуса
// Унарный минус возвращает раицональное число с противоположным знаком
// Унарный плюс возвращает рациональное число, равное текущему
BOOST_AUTO_TEST_CASE(Implementatio_of_unary_minus)
{
	CheckingRationalNumber(-CRational(2, 3), -2, 3);
	CheckingRationalNumber(-CRational(-2, 3), 2, 3);
	CheckingRationalNumber(-CRational(-2, -3), -2, 3);
}
BOOST_AUTO_TEST_CASE(Implementatio_of_unary_plus)
{
	CheckingRationalNumber(+CRational(2, 3), 2, 3);
	CheckingRationalNumber(+CRational(-2, 3), -2, 3);
	CheckingRationalNumber(+CRational(-2, -3), 2, 3);
	CheckingRationalNumber(+CRational(2, -3), -2, 3);
}
// Реализация бинарного +
BOOST_AUTO_TEST_CASE(Implementation_of_binary_addition)
{
	CheckingRationalNumber(CRational(1, 2) + CRational(1, 6), 2, 3);
	CheckingRationalNumber(CRational(1, 3) + CRational(1, 5), 8, 15);
	CheckingRationalNumber(CRational(1, 4) + CRational(7, 4), 2, 1);
	CheckingRationalNumber(CRational(2, 4) + CRational(2, 4), 1, 1);

	CheckingRationalNumber(CRational(1, 2) + 1, 3, 2);
	CheckingRationalNumber(1 + CRational(1, 2), 3, 2);

	CheckingRationalNumber(CRational(-1, 2) + CRational(-1, 6), -2, 3);
	CheckingRationalNumber(CRational(-1, 2) + CRational(1, 6), -1, 3);
	CheckingRationalNumber(CRational(1, 2) + CRational(-1, 6), 1, 3);
	CheckingRationalNumber(-1 + CRational(1, 6), -5, 6);
	CheckingRationalNumber(1 + CRational(-1, 6), 5, 6);

	CheckingRationalNumber(0 + CRational(-1, 6), -1, 6);
	CheckingRationalNumber(CRational(-1, 6) + 0, -1, 6);
	CheckingRationalNumber(CRational(1, 2) + CRational(0, 1), 1, 2);
	CheckingRationalNumber(CRational(0, 1) + CRational(1, 2), 1, 2);
	CheckingRationalNumber(CRational(0, 1) + CRational(0, 1), 0, 1);
	CheckingRationalNumber(CRational(1, 2) + CRational(-1, 2), 0, 1);
	CheckingRationalNumber(CRational(-1, 3) + CRational(1, 3), 0, 1);

	CheckingRationalNumber(CRational(1000000, 1) + CRational(1, 1000000), 1000000000001, 1000000);
}
// Реализация бинарного -
BOOST_AUTO_TEST_CASE(Implementation_of_binary_difference)
{
	CheckingRationalNumber(CRational(1, 2) - CRational(1, 6), 1, 3);
	CheckingRationalNumber(CRational(1, 3) - CRational(1, 5), 2, 15);
	CheckingRationalNumber(CRational(11, 4) - CRational(7, 4), 1, 1);
	CheckingRationalNumber(CRational(2, 4) - CRational(2, 4), 0, 1);

	CheckingRationalNumber(CRational(3, 2) - 1, 1, 2);
	CheckingRationalNumber(1 - CRational(1, 2), 1, 2);

	CheckingRationalNumber(CRational(-1, 2) - CRational(-1, 6), -1, 3);
	CheckingRationalNumber(CRational(-1, 2) - CRational(1, 6), -2, 3);
	CheckingRationalNumber(CRational(1, 2) - CRational(-1, 6), 2, 3);
	CheckingRationalNumber(-1 - CRational(1, 6), -7, 6);
	CheckingRationalNumber(1 - CRational(-1, 6), 7, 6);

	CheckingRationalNumber(0 - CRational(-1, 6), 1, 6);
	CheckingRationalNumber(CRational(-1, 6) - 0, -1, 6);
	CheckingRationalNumber(CRational(1, 2) - CRational(0, 1), 1, 2);
	CheckingRationalNumber(CRational(0, 1) - CRational(1, 2), -1, 2);
	CheckingRationalNumber(CRational(0, 1) - CRational(0, 1), 0, 1);
	CheckingRationalNumber(CRational(1, 2) - CRational(-1, 2), 1, 1);
	CheckingRationalNumber(CRational(-1, 3) - CRational(1, 3), -2, 3);

	CheckingRationalNumber(CRational(1000000, 1) - CRational(1, 1000000), 999999999999, 1000000);
}
// Реализация +=
BOOST_AUTO_TEST_CASE(Implementation_of_addition_with_assignment) // Сложение с присваиванием
{

}


BOOST_AUTO_TEST_SUITE_END()