#include "stdafx.h"
#include "../RationalNumbers/RationalNumbers.h"
#include <boost/optional.hpp>

void CheckingRationalNumber(const CRational& rat, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rat.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(rat.GetDenominator(), expectedDenominator);
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
	CheckingRationalNumber(CRational(0, 3), 0, 1);
	CheckingRationalNumber(CRational(-0.1, 3), 0, 1);
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
// Реализация += (Сложение с присваиванием)
BOOST_AUTO_TEST_CASE(Implementation_of_addition_with_assignment)
{
	CheckingRationalNumber(CRational(1, 2) += CRational(1, 6), 2, 3);
	CheckingRationalNumber(CRational(1, 2) += 1, 3, 2);
}
// Реализация -= (Разность с присваиванием)
BOOST_AUTO_TEST_CASE(Implementation_of_difference_with_assignment)
{
	CheckingRationalNumber(CRational(1, 2) -= CRational(1, 6), 1, 3);
	CheckingRationalNumber(CRational(1, 2) -= 1, -1, 2);
}
// Реализация *
BOOST_AUTO_TEST_CASE(Implementation_of_multiplication)
{
	CheckingRationalNumber(CRational(1, 2) * CRational(2, 3), 1, 3);
	CheckingRationalNumber(CRational(1, 2) * -3, -3, 2);
	CheckingRationalNumber(7 * CRational(2, 3), 14, 3);
}
// Реализация /
BOOST_AUTO_TEST_CASE(Implementation_of_division)
{
	CheckingRationalNumber(CRational(1, 2) / CRational(2, 3), 3, 4);
	CheckingRationalNumber(CRational(1, 2) / 5, 1, 10);
	CheckingRationalNumber(7 / CRational(2, 3), 21, 2);
	BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0), std::invalid_argument::exception);
	BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0, 1), std::invalid_argument::exception);
}
// Реализация *= 
BOOST_AUTO_TEST_CASE(Implementation_of_multiplication_with_assignment)
{
	CheckingRationalNumber(CRational(1, 2) *= CRational(2, 3), 1, 3);
	CheckingRationalNumber(CRational(1, 2) *= 3, 3, 2);
}
// Реализация /= 
BOOST_AUTO_TEST_CASE(Implementation_of_division_with_assignment)
{
	CheckingRationalNumber(CRational(1, 2) /= CRational(2, 3), 3, 4);
	CheckingRationalNumber(CRational(1, 2) /= CRational(2, 4), 1, 1);
	CheckingRationalNumber(CRational(1, 2) /= 3, 1, 6);
	BOOST_REQUIRE_THROW(CRational(1, 2) /= CRational(0), std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(1, 2) /= CRational(0, 1), std::invalid_argument);
}
// Реализация == и !=
BOOST_AUTO_TEST_CASE(Implementation_of_the_equality_comparison_operation)
{
	BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
	BOOST_CHECK(CRational(1, 3) == CRational(2, 6));
	BOOST_CHECK(CRational(4, 1) == 4);
	BOOST_CHECK(3 == CRational(3, 1));
	BOOST_CHECK(!(CRational(1, 2) == CRational(2, 3)));
	BOOST_CHECK(!(CRational(1, 2) == 7));
	BOOST_CHECK(!(3 == CRational(2, 3)));
	BOOST_CHECK(!(CRational(1, 2) != CRational(1, 2)));
	BOOST_CHECK(!(CRational(1, 3) != CRational(2, 6)));
	BOOST_CHECK(!(CRational(4, 1) != 4));
	BOOST_CHECK(!(3 != CRational(3, 1)));
	BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
	BOOST_CHECK(CRational(1, 2) != 7);
	BOOST_CHECK(3 != CRational(2, 3));
}
// Реализация <, >, <=, >=
BOOST_AUTO_TEST_SUITE(Implementation_of_comparison_operation)
BOOST_AUTO_TEST_CASE(less)
{
	BOOST_CHECK(CRational(1, 2) < 7);
	BOOST_CHECK(CRational(-1, 2) < 0);
	BOOST_CHECK(0 < CRational(1, 2));
	BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
	BOOST_CHECK(CRational(-1, 2) < CRational(1, 2));

	BOOST_CHECK(!(CRational(1, 2) < 0));
	BOOST_CHECK(!(CRational(1, 2) < CRational(1, 2)));

}

BOOST_AUTO_TEST_CASE(greater)
{
	BOOST_CHECK(CRational(3, 1) > 2);
	BOOST_CHECK(CRational(3, 1) > 0);
	BOOST_CHECK(0 > CRational(-1, 2));
	BOOST_CHECK(CRational(1, 2) > CRational(-1, 2));

	BOOST_CHECK(!(CRational(-1, 2) > 0));
	BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
	BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
	BOOST_CHECK(!(CRational(-6, 2) > CRational(-2, 1)));
}

BOOST_AUTO_TEST_CASE(less_or_equal)
{
	BOOST_CHECK(3 <= CRational(7, 2));
	BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
	BOOST_CHECK(CRational(7, 2) <= CRational(7, 2));
	BOOST_CHECK(CRational(7, 3) <= CRational(7, 2));
	BOOST_CHECK(CRational(1, 2) <= 1);
	BOOST_CHECK(0 <= CRational(1, 2));
	BOOST_CHECK(CRational(-1, 2) <= CRational(-1, 3));
}

BOOST_AUTO_TEST_CASE(greater_or_equal)
{
	BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
	BOOST_CHECK(!(3 >= CRational(8, 2)));
	BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
	BOOST_CHECK(CRational(7, 2) >= CRational(7, 2));
	BOOST_CHECK(CRational(1, 2) >= 0);
	BOOST_CHECK(1 >= CRational(1, 2));
	BOOST_CHECK(CRational(-1, 3) >= CRational(-1, 2));
}
BOOST_AUTO_TEST_SUITE_END()
// Реализация вывода рационального числа в выходной поток
BOOST_AUTO_TEST_CASE(Implementation_of_printed_to_ostream)
{
	{
		std::ostringstream output;
		output << CRational(7, 15);
		BOOST_CHECK_EQUAL(output.str(), "7/15");
	}

	{
		std::ostringstream output;
		output << CRational(3);
		BOOST_CHECK_EQUAL(output.str(), "3/1");
	}
}
// Реализация ввода рационального числа из входного потока
void CheckInputRationalNumber(const std::string& str, boost::optional<CRational> expectedResult)
{
	std::istringstream input(str);
	CRational rat;
	input >> rat;
	if (expectedResult == boost::none)
	{
		BOOST_CHECK_EQUAL(input.fail(), true); // input.fail() возвращает true, если в потоке input установлен флаг ошибки (failbit).
	}
	else
	{
		CheckingRationalNumber(rat, expectedResult->GetNumerator(), expectedResult->GetDenominator());
	}
}
BOOST_AUTO_TEST_CASE(Implementation_of_read_from_istream)
{
	CheckInputRationalNumber("7/15", CRational(7, 15));
	CheckInputRationalNumber("-1/1", CRational(-1, 1));
	CheckInputRationalNumber("0", CRational(0, 1));
	CheckInputRationalNumber("    -7/15    ", CRational(-7, 15));
	CheckInputRationalNumber("7.15", boost::none);
}
// Реализация возможности получения смешанной дроби из рационального числа
void CheckCompoundFraction(const CRational& rat, int expectedInteger, int expectedNumerator, int expectedDeniminator)
{
	BOOST_CHECK_EQUAL(rat.ToCompoundFraction().first, expectedInteger);
	BOOST_CHECK_EQUAL(rat.ToCompoundFraction().second.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(rat.ToCompoundFraction().second.GetDenominator(), expectedDeniminator);
}
BOOST_AUTO_TEST_CASE(Implementation_of_converted_to_compound_fraction)
{
	CheckCompoundFraction(CRational(9, 4), 2, 1, 4);
	CheckCompoundFraction(CRational(-9, 4), -2, -1, 4);
	CheckCompoundFraction(CRational(-9), -9, 0, 1);
	CheckCompoundFraction(CRational(1, 2), 0, 1, 2);
	CheckCompoundFraction(CRational(), 0, 0, 1);
}

BOOST_AUTO_TEST_SUITE_END()