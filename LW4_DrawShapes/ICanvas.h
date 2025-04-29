#pragma once
#include <vector>
#include <string>

struct SPoint {
    double x;
    double y;
};

class ICanvas {
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(SPoint from, SPoint to, std::string lineColor) = 0;
    virtual void FillPolygon(const std::vector<SPoint>& points, std::string fillColor) = 0;
    virtual void DrawCircle(SPoint center, double radius, std::string lineColor) = 0;
    virtual void FillCircle(SPoint center, double radius, std::string fillColor) = 0;
};