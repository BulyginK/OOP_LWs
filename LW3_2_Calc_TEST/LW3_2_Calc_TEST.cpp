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

void TestFunctionDeclaration(CCalculator& calc, const std::string& identifier, std::string expression)
{
    BOOST_CHECK(calc.DeclareFunction(identifier, expression));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NoError);
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
    BOOST_CHECK(calc.DeclareVariable("var"));
    BOOST_CHECK(!calc.DeclareVariable("var"));
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
    auto variables = calc.GetAllOperands();
    BOOST_CHECK(variables.find("nan_var") != variables.end()); // Проверяем, что переменная существует
    BOOST_CHECK(std::isnan(variables.at("nan_var"))); // Проверяем, что значение — NaN
}
// Успешное присваивание числа
BOOST_AUTO_TEST_CASE(set_variable_with_valid_number)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "42.5"));

    auto variables = calc.GetAllOperands();
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
    BOOST_CHECK(calc.DeclareVariable("var"));
    auto operandRef = calc.GetOperandRef("var");
    BOOST_CHECK(operandRef.has_value());
    // Проверяем содержимое
    if (operandRef) {
        COperand& op = operandRef->get();
        BOOST_CHECK(op.GetIdentifier() == "var");
    }
}
// Поиск несуществующей переменной
BOOST_AUTO_TEST_CASE(get_nonexistent_operand)
{
    CCalculator calc;
    auto operandRef = calc.GetOperandRef("var");
    BOOST_CHECK(!operandRef.has_value());
    BOOST_CHECK(operandRef == std::nullopt);
}
// Объявление и затем присваивание переменной
BOOST_AUTO_TEST_CASE(declare_and_set_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("var"));
    BOOST_CHECK(calc.SetVariableValue("var", "-273.15"));
    auto variables = calc.GetAllOperands();
    BOOST_CHECK(variables.at("var"), -273.15);
}
// Объявление переменной с присваиванием
BOOST_AUTO_TEST_CASE(declare_variable_with_set_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.SetVariableValue("var", "-27.15"));
    auto variables = calc.GetAllOperands();
    BOOST_CHECK(variables.at("var"), -27.15);
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
    auto variables = calc.GetAllOperands();
    BOOST_CHECK(variables.at("y"), 10.0);
}
// Ошибка: попытка установить переменную в значение несуществующей переменной
BOOST_AUTO_TEST_CASE(set_variable_to_nonexistent_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(!calc.SetVariableValue("y", "var"));
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
    auto variables = calc.GetAllOperands();
    BOOST_CHECK(variables.at("a"), 5.0);
    BOOST_CHECK(variables.at("b"), 5.0);
    BOOST_CHECK(variables.at("c"), 5.0);
}
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
    BOOST_CHECK(!calc.DeclareFunction("f", "var"));
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
    TestFunctionDeclaration(calc, "f1", "x+y");
    TestFunctionDeclaration(calc, "f2", "  x+y");
    TestFunctionDeclaration(calc, "f3", " x + y ");
    TestFunctionDeclaration(calc, "f4", "x+ y");
    TestFunctionDeclaration(calc, "f5", "x +y ");
    TestFunctionDeclaration(calc, "f6", "x+y    ");
}
// Успех: корректное выражение функции через другую функцию
BOOST_AUTO_TEST_CASE(declare_function_with_correct_expression_with_function)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.DeclareVariable("z"));
    TestFunctionDeclaration(calc, "f1", "x+y");
    TestFunctionDeclaration(calc, "f2", "f1-z");
}
// Ошибка: неверное выражение функции (недостающий операнд)
BOOST_AUTO_TEST_CASE(declare_function_with_incomplete_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("a"));
    BOOST_CHECK(!calc.DeclareFunction("f1", "a+"));
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::IncorrectExpression);
}
// Ошибка: некорректные идентификаторы в выражении
BOOST_AUTO_TEST_CASE(declare_function_with_invalid_operands)
{
    CCalculator calc;
    BOOST_CHECK(!calc.DeclareFunction("f", "1x+2y")); // Некорректные имена
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::IncorrectExpression);
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
// Тест на успешный подсчет значения переменной
BOOST_AUTO_TEST_CASE(count_value_of_existing_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "10.5"));
    auto result = calc.CountValue("x");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(result.value(), 10.5);
}
// Тест на отсутствие значения у неинициализированной переменной
BOOST_AUTO_TEST_CASE(count_value_of_uninitialized_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("y"));
    auto result = calc.CountValue("y");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(std::isnan(result.value())); // Проверка на NaN
}
// Тест на попытку подсчета несуществующего операнда
BOOST_AUTO_TEST_CASE(count_value_of_nonexistent_operand)
{
    CCalculator calc;
    auto result = calc.CountValue("x");
    BOOST_CHECK(!result.has_value());
    BOOST_CHECK(calc.GetErrorDescription() == ErrorDescription::NameNotExist);
}
// Тест на корректность расчета через Calculate
BOOST_AUTO_TEST_CASE(calculate_existing_variable_value)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("z"));
    BOOST_CHECK(calc.SetVariableValue("z", "-3.14"));
    double res = 0;
    double calculated = calc.Calculate("z", res);
    BOOST_CHECK(calculated, -3.14);
}
// Тест на расчет неинициализированной переменной
BOOST_AUTO_TEST_CASE(calculate_uninitialized_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("w"));
    double res = 0;
    double calculated = calc.Calculate("w", res);
    BOOST_CHECK(std::isnan(calculated));
}
// Тест на расчет несуществующей переменной
BOOST_AUTO_TEST_CASE(calculate_nonexistent_variable)
{
    CCalculator calc;
    double res = 42.0;
    double calculated = calc.Calculate("y", res);
    BOOST_CHECK(calculated, 42.0);
}
// Тест на вычисление простой функции-идентификатора (ссылки на переменную)
BOOST_AUTO_TEST_CASE(calculate_function_identifier_referencing_variable)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "5.0"));
    BOOST_CHECK(calc.DeclareFunction("ref", "x")); // fn ref = x
    double result = 0;
    double calculated = calc.Calculate("ref", result);
    BOOST_CHECK(calculated, 5.0);
}
// Тест на вычисление цепочки функций-идентификаторов
BOOST_AUTO_TEST_CASE(calculate_function_identifier_chain)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.SetVariableValue("x", "10.0"));
    BOOST_CHECK(calc.DeclareFunction("f1", "x")); // fn ref1 = base
    BOOST_CHECK(calc.DeclareFunction("f2", "f1")); // fn ref2 = ref1
    double result = 0;
    double calculated = calc.Calculate("f2", result);
    BOOST_CHECK(calculated, 10.0);
}
// Тест на обработку неинициализированной переменной через функцию-идентификатор
BOOST_AUTO_TEST_CASE(calculate_function_identifier_with_uninitialized_var)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("var"));
    BOOST_CHECK(calc.DeclareFunction("f1", "var")); // fn f1 = var
    double result = 0;
    double calculated = calc.Calculate("f1", result);
    BOOST_CHECK(std::isnan(calculated));
}
// Тест на сложение двух переменных
BOOST_AUTO_TEST_CASE(calculate_addition_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.SetVariableValue("x", "2.5"));
    BOOST_CHECK(calc.SetVariableValue("y", "3.5"));
    BOOST_CHECK(calc.DeclareFunction("sum", "x+y"));
    auto result = calc.CountValue("sum");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(result.value(), 6.0);
}
// Тест на вычитание
BOOST_AUTO_TEST_CASE(calculate_subtraction_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("a"));
    BOOST_CHECK(calc.DeclareVariable("b"));
    BOOST_CHECK(calc.SetVariableValue("a", "10.0"));
    BOOST_CHECK(calc.SetVariableValue("b", "7.5"));
    BOOST_CHECK(calc.DeclareFunction("sub", "a-b"));
    auto result = calc.CountValue("sub");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(result.value(), 2.5);
}
// Тест на умножение
BOOST_AUTO_TEST_CASE(calculate_multiplication_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("m"));
    BOOST_CHECK(calc.DeclareVariable("n"));
    BOOST_CHECK(calc.SetVariableValue("m", "3.0"));
    BOOST_CHECK(calc.SetVariableValue("n", "4.0"));
    BOOST_CHECK(calc.DeclareFunction("mul", "m*n"));
    auto result = calc.CountValue("mul");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(result.value(), 12.0);
}
// Тест на деление
BOOST_AUTO_TEST_CASE(calculate_division_expression)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("p"));
    BOOST_CHECK(calc.DeclareVariable("q"));
    BOOST_CHECK(calc.SetVariableValue("p", "15.0"));
    BOOST_CHECK(calc.SetVariableValue("q", "5.0"));
    BOOST_CHECK(calc.DeclareFunction("div", "p/q"));
    auto result = calc.CountValue("div");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(result.value(), 3.0);
}
// Тест на выражение с неинициализированными переменными
BOOST_AUTO_TEST_CASE(calculate_expression_with_uninitialized_vars)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("u"));
    BOOST_CHECK(calc.DeclareVariable("v"));
    BOOST_CHECK(calc.DeclareFunction("sum", "u+v"));
    auto result = calc.CountValue("sum");
    BOOST_CHECK(result.has_value());
    BOOST_CHECK(std::isnan(result.value()));
}
// Тест на сложную цепочку выражений
BOOST_AUTO_TEST_CASE(calculate_nested_expressions)
{
    CCalculator calc;
    BOOST_CHECK(calc.DeclareVariable("x"));
    BOOST_CHECK(calc.DeclareVariable("y"));
    BOOST_CHECK(calc.DeclareVariable("z"));
    BOOST_CHECK(calc.SetVariableValue("x", "2.0"));
    BOOST_CHECK(calc.SetVariableValue("y", "3.0"));
    BOOST_CHECK(calc.SetVariableValue("z", "4.0"));
    BOOST_CHECK(calc.DeclareFunction("sum", "x+y"));
    BOOST_CHECK(calc.DeclareFunction("f1", "sum*z"));
    auto result = calc.CountValue("f1");
    BOOST_CHECK(result.value(), 20.0);
}

BOOST_AUTO_TEST_SUITE_END()