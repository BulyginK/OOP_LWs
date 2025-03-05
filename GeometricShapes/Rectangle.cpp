#include "stdafx.h"

#include "Rectangle.h"

CRectangle::CRectangle(SPoint const& leftTop, SPoint const& rightBottom, std::string const& outlineColor, std::string const& fillColor)
	: m_leftTop(leftTop) 
	, m_rightBottom(rightBottom)
	, CSolidShape("Rectangle", outlineColor, fillColor)
{
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

double CRectangle::GetWidth() const
{
	return abs(m_leftTop.x - m_rightBottom.x);
}

double CRectangle::GetHeight() const
{
	return abs(m_leftTop.y - m_rightBottom.y);
}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

SPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

void CRectangle::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);
	strm << "\tLeftTopPoint(" << m_leftTop.x << ", " << m_leftTop.y << ")" << "\n"
		 << "\tRightBottomPoint(" << m_rightBottom.x << ", " << m_rightBottom.y << ")" << "\n";
}
