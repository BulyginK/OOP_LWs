#include "stdafx.h" 
#include "Triangle.h"

CTriangle::CTriangle(SPoint const& vertex1, SPoint const& vertex2, SPoint const& vertex3, std::string const& outlineColor, std::string const& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape("Triangle", outlineColor, fillColor)
{
}

double CTriangle::GetArea() const
{
	double side1;
	double side2;
	double side3;
	std::tie(side1, side2, side3) = GetSides();

	double perimeterHalf = CTriangle::GetPerimeter() * 0.5;
	return sqrt(perimeterHalf * (perimeterHalf - side1) * (perimeterHalf - side2) * (perimeterHalf - side3));
}

double CTriangle::GetPerimeter() const
{
	double side1;
	double side2;
	double side3;
	std::tie(side1, side2, side3) = GetSides();
	return side1 + side2 + side3;
}

std::tuple<double, double, double> CTriangle::GetSides() const
{
	auto side1 = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	auto side2 = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	auto side3 = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	return std::make_tuple(side1, side2, side3);
}

SPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);
	strm << "\tVertex1(" << m_vertex1.x << ", " << m_vertex1.y << ")" << "\n"
		 << "\tVertex2(" << m_vertex2.x << ", " << m_vertex2.y << ")" << "\n"
		 << "\tVertex3(" << m_vertex3.x << ", " << m_vertex3.y << ")" << "\n";
}

void CTriangle::Draw(ICanvas& canvas) const
{
	// Преобразуем цвета из строкового формата в uint32_t
	uint32_t outlineColor = std::stoul(GetOutlineColor(), nullptr, 16);
	uint32_t fillColor = std::stoul(GetFillColor(), nullptr, 16);

	// Вычисляем координаты углов прямоугольника
	std::vector<SPoint> points = {
		m_vertex1,
		m_vertex2,
		m_vertex3
	};

	// Рисуем залитый прямоугольник
	canvas.FillPolygon(points, fillColor);

	// Рисуем контур прямоугольника (линиями)
	canvas.DrawLine(m_vertex1, m_vertex2, outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, outlineColor);
}