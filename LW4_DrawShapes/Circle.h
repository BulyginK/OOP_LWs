#pragma once
#include "SolidShape.h"
#include "CanvasDrawable.h"

class CCircle final
	: public CSolidShape
	, public CCanvasDrawable
{
public:
	CCircle(SPoint const& center, double const& radius, std::string const& outlineColor, std::string const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	SPoint GetCenter() const;
	double GetRadius() const;

	void Draw(ICanvas& canvas) const override;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	SPoint m_center;
	double m_radius;
};