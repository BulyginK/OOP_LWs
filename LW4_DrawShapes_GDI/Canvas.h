#pragma once
#include <windows.h> 
#include "ICanvas.h"

class CCanvas final : public ICanvas {
public:
    explicit CCanvas(HDC hdc) : m_hdc(hdc) {}

    void DrawLine(SPoint from, SPoint to, uint32_t lineColor) override;

    void FillPolygon(const std::vector<SPoint>& points, uint32_t fillColor) override;

    void DrawCircle(SPoint center, double radius, uint32_t lineColor) override;

    void FillCircle(SPoint center, double radius, uint32_t fillColor) override;

private:
    HDC m_hdc;  // Контекст устройства (Device Context)

    static COLORREF ColorFromUInt(uint32_t color);
    static RECT GetCircleRect(SPoint center, double radius);
};