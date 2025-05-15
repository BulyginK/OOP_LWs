#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape
	: public ISolidShape
	, public CShape
{
public:
	CSolidShape(const std::string& type, const std::string& outlineColor, const std::string& fillColor);
	virtual ~CSolidShape() = default;

	std::string GetFillColor() const override final;

	std::string ToString() const override final;

protected:
	virtual void AppendProperties(std::ostream& strm) const = 0;

private:
	std::string m_type;
	std::string m_fillColor;
};