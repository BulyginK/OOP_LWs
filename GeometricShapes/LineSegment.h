#pragma once
#include "Shape.h"

class CLineSegment final
	: public CShape
{
public:
	CLineSegment(SPoint const& startPoint, SPoint const& endPoint, std::string const& outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	SPoint GetStartPoint() const;
	SPoint GetEndPoint() const;

	std::string ToString() const override;

private:
	SPoint m_startPoint;
	SPoint m_endPoint;
};
