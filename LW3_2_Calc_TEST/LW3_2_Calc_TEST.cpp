#include "stdafx.h"

#include "../LW3_2_Calc/Calculator.h"
#include "../LW3_2_Calc/Variable.h"

struct CalculatorFixture
{
	CCalculator calc;
};

// Калькулятор
BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)
// Тест: можно установить новую переменную с корректным именем
BOOST_AUTO_TEST_CASE(can_set_new_variable)
{
    BOOST_CHECK(calc.DeclareVariable("valid_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Тест: нельзя установить переменную с некорректным именем
BOOST_AUTO_TEST_CASE(cannot_set_variable_with_invalid_name)
{
    BOOST_CHECK(!calc.DeclareVariable("123invalid_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Тест: нельзя установить переменную с пустым именем
BOOST_AUTO_TEST_CASE(cannot_set_variable_with_empty_name)
{
    BOOST_CHECK(!calc.DeclareVariable(""));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Тест: нельзя установить переменную с уже существующим именем
BOOST_AUTO_TEST_CASE(cannot_set_duplicate_variable)
{
    BOOST_CHECK(calc.DeclareVariable("existing_var"));
    BOOST_CHECK(!calc.DeclareVariable("existing_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::DuplicateName);
}
// Тест: можно установить несколько переменных с разными именами
BOOST_AUTO_TEST_CASE(can_set_multiple_variables)
{
    BOOST_CHECK(calc.DeclareVariable("var1"));
    BOOST_CHECK(calc.DeclareVariable("var2"));
    BOOST_CHECK(calc.DeclareVariable("var3"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Тест: проверка, что переменная устанавливается с значением NaN
BOOST_AUTO_TEST_CASE(variable_is_set_to_nan)
{
    BOOST_CHECK(calc.DeclareVariable("nan_var"));
    // Проверяем, что переменная объявлена и её значение — NaN
    auto variables = calc.GetAllVariables();
    BOOST_CHECK(variables.find("nan_var") != variables.end()); // Проверяем, что переменная существует
    BOOST_CHECK(std::isnan(variables.at("nan_var"))); // Проверяем, что значение — NaN
}

BOOST_AUTO_TEST_SUITE_END()