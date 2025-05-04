#include "stdafx.h"
#include "../LW5_ComplexNumbers/Complex.h"
#include <boost/optional.hpp>

void CheckingComplexNumber(const CComplex& compNum, double expectedReal, double expectedImage)
{
	BOOST_CHECK_EQUAL(compNum.Re(), expectedReal);
	BOOST_CHECK_EQUAL(compNum.Im(), expectedImage);
}

BOOST_AUTO_TEST_SUITE(Checking_the_created_complex_number)
// конструктор по умолчанию
BOOST_AUTO_TEST_CASE(Constructor_tests)
{
	CheckingComplexNumber(CComplex(), 0, 0);
}
// вещественное число (мнимая часть = 0)
BOOST_AUTO_TEST_CASE(Real_number_constructor)
{
	CheckingComplexNumber(CComplex(5.0), 5.0, 0);
	CheckingComplexNumber(CComplex(-3.14), -3.14, 0);
}
BOOST_AUTO_TEST_SUITE_END()