#include "stdafx.h"
#include "SolidShape.h"

CSolidShape::CSolidShape(const std::string& type, const std::string& outlineColor, const std::string& fillColor)
	: CShape(outlineColor)
	, m_type(type)
	, m_fillColor(fillColor)
{
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);
	strm << m_type << ":\n"
			 << "\tarea = " << GetArea() << "\n"
			 << "\tperimeter = " << GetPerimeter() << "\n"
			 << "\toutline color = #" << GetOutlineColor() << "\n"
			 << "\tfill color = #" << GetFillColor() << std::endl;
	AppendProperties(strm);
	return strm.str();
}

// можно вызывать методы родителей напрямую -пдумать как это реализовать чтобы не было ромбовидного наследования