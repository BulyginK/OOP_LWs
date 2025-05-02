#pragma once
#include <windows.h> 
#include "ICanvas.h"

//class CCanvas : public ICanvas {
//public:
//    void DrawLine(SPoint from, SPoint to, std::string lineColor) const;
//
//    void FillPolygon(const std::vector<SPoint>& points, std::string fillColor) const;
//
//    void DrawCircle(SPoint center, double radius, std::string lineColor) const;
//
//    void FillCircle(SPoint center, double radius, std::string fillColor) const;
//};

class CCanvas : public ICanvas {


public:
    // Конструктор принимает HDC (например, из окна или Bitmap)
    explicit CCanvas(HDC hdc) : m_hdc(hdc) {}

    void DrawLine(SPoint from, SPoint to, uint32_t lineColor) const;

    void FillPolygon(const std::vector<SPoint>& points, uint32_t fillColor) const;

    void DrawCircle(SPoint center, double radius, uint32_t lineColor) const;

    void FillCircle(SPoint center, double radius, uint32_t fillColor) const;

private:
    HDC m_hdc;  // Контекст устройства (Device Context)
};