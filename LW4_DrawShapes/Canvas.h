#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas {
public:
    void DrawLine(SPoint from, SPoint to, std::string lineColor) override;

    void FillPolygon(const std::vector<SPoint>& points, std::string fillColor) override;

    void DrawCircle(SPoint center, double radius, std::string lineColor) override;

    void FillCircle(SPoint center, double radius, std::string fillColor) override;
};