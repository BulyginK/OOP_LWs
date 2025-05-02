#include "stdafx.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(SPoint const& startPoint, SPoint const& endPoint, std::string const& outlineColor)
	: CShape(outlineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint){};

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	SPoint startPoint = GetStartPoint();
	SPoint endPoint = GetEndPoint();
	return hypot(startPoint.x - endPoint.x, startPoint.y - endPoint.y);
}

SPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

SPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << "LineSegment:" << "\n"
			 << "\tarea = " << GetArea() << "\n"
			 << "\tperimeter = " << GetPerimeter() << "\n"
			 << "\toutline color = #" << GetOutlineColor() << "\n"
			 << "\tStartPoint(" << m_startPoint.x << ", " << m_startPoint.y << ")" << "\n"
			 << "\tEndPoint(" << m_endPoint.x << ", " << m_endPoint.y << ")" << std::endl;
	return strm.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, std::stoul(GetOutlineColor(), nullptr, 16));
}
