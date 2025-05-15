#pragma once
#include <string>
#include "ICanvasDrawable.h"

class IShape 
	: virtual public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string GetOutlineColor() const = 0;
	virtual std::string ToString() const = 0;
	virtual ~IShape() = default;
};