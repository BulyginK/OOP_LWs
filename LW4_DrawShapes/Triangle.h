#pragma once
#include "SolidShape.h"

class CTriangle final
	: public CSolidShape
{
public:
	CTriangle(SPoint const& vertex1, SPoint const& vertex2, SPoint const& vertex3, 
		std::string const& outlineColor, std::string const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	SPoint GetVertex1() const;
	SPoint GetVertex2() const;
	SPoint GetVertex3() const;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	std::tuple<double, double, double> GetSides() const;
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
};