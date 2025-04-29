#pragma once
#include "IShape.h"

struct SPoint
{
public:
	double x;
	double y;
};

class CShape
	: virtual public IShape
{
public:
	CShape(const std::string& outlineColor);
	virtual ~CShape() = default;

	std::string GetOutlineColor() const override final;

private:
	std::string m_outlineColor;
};
