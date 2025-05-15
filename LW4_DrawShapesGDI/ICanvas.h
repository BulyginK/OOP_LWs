#pragma once
#include <vector>
#include <cstdint>

struct SPoint
{
    double x;
    double y;
};

class ICanvas {
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(SPoint from, SPoint to, uint32_t lineColor) = 0;
    virtual void FillPolygon(const std::vector<SPoint>& points, uint32_t fillColor) = 0;
    virtual void DrawCircle(SPoint center, double radius, uint32_t lineColor) = 0;
    virtual void FillCircle(SPoint center, double radius, uint32_t fillColor) = 0;
};