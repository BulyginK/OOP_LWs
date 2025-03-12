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
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
	BOOST_CHECK_EQUAL(GCD(7, 7), 7u);
	BOOST_CHECK_EQUAL(GCD(1, 10), 1u);
	BOOST_CHECK_EQUAL(GCD(10, 1), 1u);
	BOOST_CHECK_EQUAL(GCD(655360001, 562448657), 1u);
	BOOST_CHECK_EQUAL(GCD(123456789, 987654321), 9u);
	BOOST_CHECK_EQUAL(GCD(-2, 4), 2u);
	BOOST_CHECK_EQUAL(GCD(4, -2), 2u);
}
// Конструируется рациональное число, равное numerator/denominator
BOOST_AUTO_TEST_CASE(Constructor_with_two_parameters)
{
	CheckingRationalNumber(CRational(2, 3), 2, 3);
	CheckingRationalNumber(CRational(5, 1), 5, 1);
	CheckingRationalNumber(CRational(5, -1), -5, 1); // знаменатель положительный, числитель может быть отрицательным
	CheckingRationalNumber(CRational(-5, -1), 5, 1);
	CheckingRationalNumber(CRational(6, 8), 5, 1);
	CheckingRationalNumber(CRational(6, -8), 5, 1);
}
// Знаменатель равен 0 - выброшено исключение
BOOST_AUTO_TEST_CASE(Denominator_is_0)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(-1, 0), std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(0, 0), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()