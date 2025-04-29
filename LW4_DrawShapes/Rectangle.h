#pragma once
#include "SolidShape.h"

class CRectangle final
	: public CSolidShape
{
public:
	CRectangle(SPoint const& leftTop, SPoint const& rightBottom, 
		std::string const& outlineColor, std::string const& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	SPoint GetLeftTop() const;
	SPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	SPoint m_leftTop;
	SPoint m_rightBottom;
};
