#include "fakeit.hpp"
#include "CanvasMock.h"
#include "../LW4_DrawShapes_GDI/Canvas.h"
#include "../LW4_DrawShapes_GDI/Circle.h"


using namespace fakeit;

BOOST_AUTO_TEST_CASE(test_circle_draw)
{
    // Обнуляем лог
    CanvasMock::Reset();

    // Создаем мок объекта ICanvas
    Mock<ICanvas> mock;
    ICanvas& canvas = mock.get();

    // Устанавливаем логирование вызова DrawCircle
    When(Method(mock, DrawCircle))
        .Do([](SPoint center, double radius, uint32_t color)
            {
                CanvasMock::instance->calls.push_back("DrawCircle");
            });

    // Создаем фигуру и вызываем Draw
    CCircle circle({ 0, 0 }, 10, "ff0000", "00ff00");
    circle.Draw(canvas);

    // Проверяем, что вызов был зафиксирован
    BOOST_CHECK_EQUAL(CanvasMock::instance->calls.size(), 1);
    BOOST_CHECK_EQUAL(CanvasMock::instance->calls[0], "DrawCircle");
}
