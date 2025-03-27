#include "stdafx.h"

#include "../LW3_2_Calc/Calculator.h"
#include "../LW3_2_Calc/Variable.h"
#include "../LW3_2_Calc/FunctionIdentifier.h"
#include "../LW3_2_Calc/FunctionExpression.h"

struct CalculatorFixture
{
	CCalculator calc;
};

void CheckValidDeclaration(CCalculator& calc, const std::string& varName)
{
    BOOST_CHECK(calc.DeclareVariable(varName));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}

void CheckInvalidDeclaration(CCalculator& calc, const std::string& varName)
{
    BOOST_CHECK(!calc.DeclareVariable(varName));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}

// Калькулятор
BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)
// Тест: можно установить новую переменную с корректным именем
BOOST_AUTO_TEST_CASE(can_set_new_variable)
{
    CCalculator calc;
    CheckValidDeclaration(calc, "valid_var");
    CheckValidDeclaration(calc, "_valid_var");
    CheckValidDeclaration(calc, "__Valid__Var__");
}
// Тест: нельзя установить переменную с некорректным именем
BOOST_AUTO_TEST_CASE(cannot_set_variable_with_invalid_name)
{
    CCalculator calc;
    CheckInvalidDeclaration(calc, "123invalid_var");
    CheckInvalidDeclaration(calc, "_");
    CheckInvalidDeclaration(calc, "__");
    CheckInvalidDeclaration(calc, "__invalid_var!!");
    CheckInvalidDeclaration(calc, "invalid-var");
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
    BOOST_CHECK(calc.SetVariableValue("x", "42.5"));

    auto variables = calc.GetAllVariables();
    BOOST_CHECK(variables.find("x") != variables.end());
    BOOST_CHECK(variables.at("x"), 42.5);
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
// Ошибка: некорректное значение (пустая строка)
BOOST_AUTO_TEST_CASE(set_variable_with_not)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!calc.SetVariableValue("y", "")); // Пустая строка
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
    BOOST_CHECK(variables.at("temp"), -273.15);
}
// Объявление переменной с присваиванием
BOOST_AUTO_TEST_CASE(declare_variable_with_set_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.SetVariableValue("temp", "-27.15"));
    auto variables = calc.GetAllVariables();
    BOOST_CHECK(variables.at("temp"), -27.15);
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
    BOOST_CHECK(variables.at("y"), 10.0);
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
    BOOST_CHECK(variables.at("a"), 5.0);
    BOOST_CHECK(variables.at("b"), 5.0);
    BOOST_CHECK(variables.at("c"), 5.0);
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

// Успех: объявление функции с существующей переменной
BOOST_AUTO_TEST_CASE(declare_function_with_valid_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareFunction("f", "x"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Ошибка: попытка объявить функцию с несуществующей переменной
BOOST_AUTO_TEST_CASE(declare_function_with_nonexistent_variable)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DeclareFunction("f", "nonexistent_var"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NameNotExist);
}
// Ошибка: некорректный идентификатор функции
BOOST_AUTO_TEST_CASE(declare_function_with_invalid_identifier)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DeclareFunction("123func", "x"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Ошибка: повторное объявление функции
BOOST_AUTO_TEST_CASE(redeclare_existing_function)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareFunction("f", "x"));
    BOOST_CHECK(!calc.DeclareFunction("f", "x"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::DuplicateName);
}
// Успех: цепочка функций
BOOST_AUTO_TEST_CASE(function_chain_declaration)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareFunction("f1", "x"));
    BOOST_CHECK(calc.DeclareFunction("f2", "f1"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Успех: объявление функции с простым выражением (сложение)
BOOST_AUTO_TEST_CASE(declare_function_with_valid_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.DeclareFunction("sum", "x+y"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Успех: корректное выражение функции
BOOST_AUTO_TEST_CASE(declare_function_with_correct_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.DeclareVariable("z"));
    BOOST_CHECK(calc.DeclareFunction("f1", "x+y")); // Корректное выражение
    BOOST_CHECK(calc.DeclareFunction("f2", "f1-z")); // Корректное выражение
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
}
// Ошибка: неверное выражение функции (недостающий операнд)
BOOST_AUTO_TEST_CASE(declare_function_with_incomplete_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("a"));
    BOOST_CHECK(!calc.DeclareFunction("f1", "a+"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Ошибка: некорректные идентификаторы в выражении
BOOST_AUTO_TEST_CASE(declare_function_with_invalid_operands)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DeclareFunction("f", "1x+2y")); // Некорректные имена
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::InvalidUsage);
}
// Успех: корректная работа функции проверки вида операции
BOOST_AUTO_TEST_CASE(declare_function_with_valid_expression_with_all_sign)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(CFunctionExpression::IsCorrectFunctionExpression("x+y"));
    BOOST_CHECK(CFunctionExpression::IsCorrectFunctionExpression("x-y"));
    BOOST_CHECK(CFunctionExpression::IsCorrectFunctionExpression("x*y"));
    BOOST_CHECK(CFunctionExpression::IsCorrectFunctionExpression("x/y"));
}
// Ошибка: корректная работа функции проверки не предусмотренных видов операций
BOOST_AUTO_TEST_CASE(declare_function_with_invalid_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x\\y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x_y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x%y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x^y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x**y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x&y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x<<y"));
    BOOST_CHECK(!CFunctionExpression::IsCorrectFunctionExpression("x>>y"));
}
// Ошибка: повторное объявление функции-выражения
BOOST_AUTO_TEST_CASE(redeclare_function_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("a"));
    BOOST_CHECK(calc.DeclareVariable("b"));
    BOOST_CHECK(calc.DeclareFunction("f", "a+b"));
    BOOST_CHECK(!calc.DeclareFunction("f", "a-b")); // Повторное объявление
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::DuplicateName);
}


BOOST_AUTO_TEST_SUITE_END()