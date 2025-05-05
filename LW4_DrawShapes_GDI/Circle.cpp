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
	canvas.DrawCircle(m_center, m_radius, std::stoul(GetOutlineColor(), nullptr, 16));  // конвертируем строку в unsigned long
	canvas.FillCircle(m_center, m_radius, std::stoul(GetFillColor(), nullptr, 16));
	
	// тк DrawCircle(SPoint center, double radius, uint32_t lineColor) принимает uint32_t lineColor, а у нас он хранится в string - приводим к типу uint32_t
	// uint32_t — беззнаковое (unsigned) 32-битное целое число
	// unsigned long stoul(const std::string& str, size_t* pos = 0, int base = 10);
	// str — строка для преобразования,
	// pos — указатель на переменную, куда запишется индекс первого непрочитанного символа(если передан nullptr, эта информация игнорируется),
	// base — система счисления(2–36).В данном случае 16 (шестнадцатеричная).
}