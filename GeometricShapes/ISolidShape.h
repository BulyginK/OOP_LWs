#pragma once
#include "IShape.h"

class ISolidShape
	: virtual public IShape  
{
public:
	virtual std::string GetFillColor() const = 0;
	virtual ~ISolidShape() = default;
};