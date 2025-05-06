#include "Canvas.h"

void CCanvas::DrawLine(SPoint from, SPoint to, uint32_t lineColor) 
{
    // ����
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

    // ����������� ����� � ������ POINT (����� ��� GDI)
    std::vector<POINT> gdiPoints;
    for (const auto& p : points) {
        gdiPoints.push_back({ static_cast<LONG>(p.x), static_cast<LONG>(p.y) });
    }

    // ������ � �������� �������
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdc, hBrush));
    Polygon(m_hdc, gdiPoints.data(), (int)gdiPoints.size());
    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}

void CCanvas::DrawCircle(SPoint center, double radius, uint32_t lineColor) 
{
    // ����
    HPEN hPen = CreatePen(PS_SOLID, 1, ColorFromUInt(lineColor));
    HPEN hOldPen = static_cast<HPEN>(SelectObject(m_hdc, hPen));

    RECT rc = GetCircleRect(center, radius);
    Ellipse(m_hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(m_hdc, hOldPen);
    DeleteObject(hPen);
}

void CCanvas::FillCircle(SPoint center, double radius, uint32_t fillColor) 
{
    // �����
    HBRUSH hBrush = CreateSolidBrush(ColorFromUInt(fillColor));
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdc, hBrush));

    RECT rc = GetCircleRect(center, radius);
    Ellipse(m_hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}

COLORREF CCanvas::ColorFromUInt(uint32_t color) {
    return RGB(
        (color >> 16) & 0xFF,   // ������� // ������� ����� ������ �� 16 ��� // &0xFF � ����� ��� ��������� ������ ������� 8 ���
        (color >> 8) & 0xFF,    // ������ // ���������� ������ �� 8 ���
        color & 0xFF            // ����� // ��� ������
    );
}

RECT CCanvas::GetCircleRect(SPoint center, double radius) { // RECT - ���������, ��� ��������� ������������ � ������� ������ �������� ���� int
    RECT rc;
    rc.left = static_cast<int>(center.x - radius);
    rc.top = static_cast<int>(center.y - radius);
    rc.right = static_cast<int>(center.x + radius);
    rc.bottom = static_cast<int>(center.y + radius);
    return rc;
}