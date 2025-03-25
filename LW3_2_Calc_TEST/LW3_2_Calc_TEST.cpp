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
// Успешное присваивание числа
BOOST_AUTO_TEST_CASE(set_variable_with_valid_number)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "42.5")); // Успешное присваивание

    auto variables = calc.GetAllVariables();
    BOOST_CHECK(variables.find("x") != variables.end());
    BOOST_CHECK_CLOSE(variables.at("x"), 42.5, 1e-6); // Проверяем значение с допустимой погрешностью
}
// Ошибка: неверный идентификатор переменной
BOOST_AUTO_TEST_CASE(set_variable_with_invalid_identifier)
{
    CCalculator calc;
    BOOST_CHECK(!calc.SetVariableValue("123x", "10")); // Идентификатор не может начинаться с цифры
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Ошибка: некорректное значение (не число)
BOOST_AUTO_TEST_CASE(set_variable_with_invalid_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!calc.SetVariableValue("y", "abc")); // Не число
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::IncorrectIdentifier);
}
// Корректные числа
BOOST_AUTO_TEST_CASE(parse_valid_numbers)
{
    CCalculator calc;
    BOOST_CHECK(calc.DetermineNewValueOfVariable("123").value() == 123.0);
    BOOST_CHECK(calc.DetermineNewValueOfVariable("-45.67").value() == -45.67);
    BOOST_CHECK(calc.DetermineNewValueOfVariable("0.5").value() == 0.5);
}
// Некорректные числа
BOOST_AUTO_TEST_CASE(parse_invalid_numbers)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DetermineNewValueOfVariable("123abc").has_value()); // Лишние символы
    BOOST_CHECK(!calc.DetermineNewValueOfVariable("12.34.56").has_value()); // Две точки
    BOOST_CHECK(!calc.DetermineNewValueOfVariable("").has_value()); // Пустая строка
}
// Граничные случаи
BOOST_AUTO_TEST_CASE(parse_edge_cases)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DetermineNewValueOfVariable("1e999").has_value());
    BOOST_CHECK(calc.DetermineNewValueOfVariable("007").value() == 7.0); 
    BOOST_CHECK(!calc.DetermineNewValueOfVariable("-").has_value());
}
// Поиск существующей переменной
BOOST_AUTO_TEST_CASE(get_existing_operand)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("test_var"));
    auto operandRef = calc.GetOperandRef("test_var");
    BOOST_CHECK(operandRef.has_value());
    // Проверяем содержимое
    if (operandRef) {
        COperand& op = operandRef->get();
        BOOST_CHECK(op.GetIdentifier() == "test_var");
    }
}
// Поиск несуществующей переменной
BOOST_AUTO_TEST_CASE(get_nonexistent_operand)
{
    CCalculator calc;
    auto operandRef = calc.GetOperandRef("ghost_var");
    BOOST_CHECK(!operandRef.has_value());
    BOOST_CHECK(operandRef == std::nullopt);
}
// Объявление и затем присваивание переменной
BOOST_AUTO_TEST_CASE(declare_and_set_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("temp"));
    BOOST_CHECK(calc.SetVariableValue("temp", "-273.15"));
    auto variables = calc.GetAllVariables();
    BOOST_CHECK_CLOSE(variables.at("temp"), -273.15, 1e-6);
}
// Объявление переменной с присваиванием
BOOST_AUTO_TEST_CASE(declare_variable_with_set_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.SetVariableValue("temp", "-27.15"));
    auto variables = calc.GetAllVariables();
    BOOST_CHECK_CLOSE(variables.at("temp"), -27.15, 1e-6);
}
// Ошибка: некорректное значение ранее объявленного идентификатора
BOOST_AUTO_TEST_CASE(set_right_variable_with_invalid_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!calc.SetVariableValue("y", "12abc"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::IncorrectIdentifier);
}
// Успех: переменная устанавливается в значение другой переменной
BOOST_AUTO_TEST_CASE(set_variable_to_another_variable_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "10"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.SetVariableValue("y", "x"));
    auto variables = calc.GetAllVariables();
    BOOST_CHECK_CLOSE(variables.at("y"), 10.0, 1e-9);
}
// Ошибка: попытка установить переменную в значение несуществующей переменной
BOOST_AUTO_TEST_CASE(set_variable_to_nonexistent_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!calc.SetVariableValue("y", "nonexistent"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::IncorrectIdentifier);
}
// Успех: последовательное присваивание переменных
BOOST_AUTO_TEST_CASE(chained_variable_assignment)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("a"));
    BOOST_CHECK(calc.SetVariableValue("a", "5"));
    BOOST_CHECK(calc.DeclareVariable("b"));
    BOOST_CHECK(calc.SetVariableValue("b", "a"));
    BOOST_CHECK(calc.DeclareVariable("c"));
    BOOST_CHECK(calc.SetVariableValue("c", "b"));
    auto variables = calc.GetAllVariables();
    BOOST_CHECK_CLOSE(variables.at("a"), 5.0, 1e-9);
    BOOST_CHECK_CLOSE(variables.at("b"), 5.0, 1e-9);
    BOOST_CHECK_CLOSE(variables.at("c"), 5.0, 1e-9);
}

// TODO
// Ошибка: циклическое присваивание переменных - 
//BOOST_AUTO_TEST_CASE(cyclic_variable_assignment)
//{
//    CCalculator calc;
//    BOOST_CHECK(calc.DeclareVariable("x"));
//    BOOST_CHECK(calc.DeclareVariable("y"));
//    BOOST_CHECK(calc.SetVariableValue("x", "10"));
//    BOOST_CHECK(calc.SetVariableValue("y", "x")); // допустимо
//    BOOST_CHECK(!calc.SetVariableValue("x", "y")); // создает цикл
//    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
//}

BOOST_AUTO_TEST_SUITE_END()