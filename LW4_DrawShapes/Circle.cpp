#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle(SPoint const& center, double const& radius, std::string const& outlineColor, std::string const& fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape("Circle", outlineColor, fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return M_PI * 2 * m_radius;
}

SPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);
	strm	<< "\tCenterPoint(" << m_center.x << ", " << m_center.y << ")" << "\n"
			<< "\tradius = " << m_radius << "\n";
}

void CCircle::Draw(ICanvas& canvas) const 
{
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
	canvas.FillCircle(m_center, m_radius, GetFillColor());
}