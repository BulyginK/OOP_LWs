#include "stdafx.h"

#include "../LW3_2_Calc/Calculator.h"

struct CalculatorFixture
{
	CCalculator calc;
};

// Калькулятор
BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)
// Тест: можно установить новую переменную с корректным именем
BOOST_AUTO_TEST_CASE(can_set_new_variable)
{
    BOOST_CHECK(calc.SetVar("valid_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Тест: нельзя установить переменную с некорректным именем
BOOST_AUTO_TEST_CASE(cannot_set_variable_with_invalid_name)
{
    BOOST_CHECK(!calc.SetVar("123invalid_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Тест: нельзя установить переменную с пустым именем
BOOST_AUTO_TEST_CASE(cannot_set_variable_with_empty_name)
{
    BOOST_CHECK(!calc.SetVar(""));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Тест: нельзя установить переменную с уже существующим именем
BOOST_AUTO_TEST_CASE(cannot_set_duplicate_variable)
{
    BOOST_CHECK(calc.SetVar("existing_var"));
    BOOST_CHECK(!calc.SetVar("existing_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::DuplicateName);
}
// Тест: можно установить несколько переменных с разными именами
BOOST_AUTO_TEST_CASE(can_set_multiple_variables)
{
    BOOST_CHECK(calc.SetVar("var1"));
    BOOST_CHECK(calc.SetVar("var2"));
    BOOST_CHECK(calc.SetVar("var3"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Тест: проверка, что переменная устанавливается с значением NaN
BOOST_AUTO_TEST_CASE(variable_is_set_to_nan)
{
    BOOST_CHECK(calc.SetVar("nan_var"));
    BOOST_CHECK(std::isnan(calc.GetValue("nan_var")));
    BOOST_CHECK(std::isnan(calc.GetValue("not_var")));
}

BOOST_AUTO_TEST_SUITE_END()