#include "Canvas.h"

void CCanvas::DrawLine(SPoint from, SPoint to, uint32_t lineColor) 
{
    // перо
    HPEN hPen = CreatePen(PS_SOLID, 1, ColorFromUInt(lineColor));
    HPEN hOldPen = static_cast<HPEN>(SelectObject(m_hdc, hPen));

    MoveToEx(m_hdc, static_cast<int>(from.x), static_cast<int>(from.y), nullptr);
    LineTo(m_hdc, static_cast<int>(to.x), static_cast<int>(to.y));

    SelectObject(m_hdc, hOldPen);
    DeleteObject(hPen);
}

void CCanvas::FillPolygon(const std::vector<SPoint>& points, uint32_t fillColor) 
{
    if (points.empty()) return;

    HBRUSH hBrush = CreateSolidBrush(ColorFromUInt(fillColor));

    // Преобразуем точки в формат POINT (нужен для GDI)
    std::vector<POINT> gdiPoints;
    for (const auto& p : points) {
        gdiPoints.push_back({ static_cast<LONG>(p.x), static_cast<LONG>(p.y) });
    }

    // Рисуем и заливаем полигон
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdc, hBrush));
    Polygon(m_hdc, gdiPoints.data(), (int)gdiPoints.size());
    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}

void CCanvas::DrawCircle(SPoint center, double radius, uint32_t lineColor) 
{
    // перо
    HPEN hPen = CreatePen(PS_SOLID, 1, ColorFromUInt(lineColor));
    HPEN hOldPen = static_cast<HPEN>(SelectObject(m_hdc, hPen));

    RECT rc = GetCircleRect(center, radius);
    Ellipse(m_hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(m_hdc, hOldPen);
    DeleteObject(hPen);
}

void CCanvas::FillCircle(SPoint center, double radius, uint32_t fillColor) 
{
    // кисть
    HBRUSH hBrush = CreateSolidBrush(ColorFromUInt(fillColor));
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdc, hBrush));

    RECT rc = GetCircleRect(center, radius);
    Ellipse(m_hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}

COLORREF CCanvas::ColorFromUInt(uint32_t color) {
    return RGB(
        (color >> 16) & 0xFF,   // Красный // битовый сдвиг вправо на 16 бит // &0xFF — маска для выделения именно младших 8 бит
        (color >> 8) & 0xFF,    // Зелёный // аналогично только на 8 бит
        color & 0xFF            // Синий // без сдвига
    );
}

RECT CCanvas::GetCircleRect(SPoint center, double radius) { // RECT - структура, кот описывает прямоуголник с помощью четырёх значений типа int
    RECT rc;
    rc.left = static_cast<int>(center.x - radius);
    rc.top = static_cast<int>(center.y - radius);
    rc.right = static_cast<int>(center.x + radius);
    rc.bottom = static_cast<int>(center.y + radius);
    return rc;
}