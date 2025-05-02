#include "Canvas.h"

void CCanvas::DrawLine(SPoint from, SPoint to, uint32_t lineColor) 
{
    // ������ ���� (Pen) � ������ ������
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(
        (lineColor >> 16) & 0xFF,  // �������
        (lineColor >> 8) & 0xFF,   // ������
        lineColor & 0xFF           // �����
    ));

    // �������� ���� � ��������
    HPEN hOldPen = (HPEN)SelectObject(m_hdc, hPen);

    // ������ �����
    MoveToEx(m_hdc, (int)from.x, (int)from.y, nullptr);
    LineTo(m_hdc, (int)to.x, (int)to.y);

    // ��������������� ������ ���� � ������� ����
    SelectObject(m_hdc, hOldPen);
    DeleteObject(hPen);
}

void CCanvas::FillPolygon(const std::vector<SPoint>& points, uint32_t fillColor) 
{
    if (points.empty()) return;

    // ������ ����� (Brush) ��� �������
    HBRUSH hBrush = CreateSolidBrush(RGB(
        (fillColor >> 16) & 0xFF,
        (fillColor >> 8) & 0xFF,
        fillColor & 0xFF
    ));

    // ����������� ����� � ������ POINT (����� ��� GDI)
    std::vector<POINT> gdiPoints;
    for (const auto& p : points) {
        gdiPoints.push_back({ (LONG)p.x, (LONG)p.y });
    }

    // ������ � �������� �������
    HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hdc, hBrush);
    Polygon(m_hdc, gdiPoints.data(), (int)gdiPoints.size());
    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}

void CCanvas::DrawCircle(SPoint center, double radius, uint32_t lineColor) 
{
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(
        (lineColor >> 16) & 0xFF,
        (lineColor >> 8) & 0xFF,
        lineColor & 0xFF
    ));
    HPEN hOldPen = (HPEN)SelectObject(m_hdc, hPen);

    // � GDI ��� DrawCircle, ���������� Ellipse
    Ellipse(m_hdc,
        (int)(center.x - radius),
        (int)(center.y - radius),
        (int)(center.x + radius),
        (int)(center.y + radius)
    );

    SelectObject(m_hdc, hOldPen);
    DeleteObject(hPen);
}

void CCanvas::FillCircle(SPoint center, double radius, uint32_t fillColor) 
{
    HBRUSH hBrush = CreateSolidBrush(RGB(
        (fillColor >> 16) & 0xFF,
        (fillColor >> 8) & 0xFF,
        fillColor & 0xFF
    ));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(m_hdc, hBrush);

    Ellipse(m_hdc,
        (int)(center.x - radius),
        (int)(center.y - radius),
        (int)(center.x + radius),
        (int)(center.y + radius)
    );

    SelectObject(m_hdc, hOldBrush);
    DeleteObject(hBrush);
}