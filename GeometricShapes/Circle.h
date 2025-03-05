#pragma once
#include "SolidShape.h"

class CCircle final
	: public CSolidShape
{
public:
	CCircle(SPoint const& center, double const& radius, std::string const& outlineColor, std::string const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	SPoint GetCenter() const;
	double GetRadius() const;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	SPoint m_center;
	double m_radius;
};