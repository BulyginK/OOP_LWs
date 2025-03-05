#include "ShapeMenu.h"
#include <boost/algorithm/string.hpp>
#include <unordered_map>

void CShapeMenu::ReadShape(std::string& commandLine)
{
	boost::to_lower(commandLine);
	ParametersList parametersList;
	boost::split(parametersList, commandLine, boost::is_any_of(" "));
	if (parametersList[0] == "triangle")
	{
		AddTriangle(parametersList);
	}
	else if (parametersList[0] == "rectangle")
	{
		AddRectangle(parametersList);
	}
	else if (parametersList[0] == "circle")
	{
		AddCircle(parametersList);
	}
	else if (parametersList[0] == "linesegment")
	{
		AddLineSegment(parametersList);
	}
	else if (parametersList[0] == "info")
	{
		PrintInfo();
	}
	else
	{
		throw std::invalid_argument("Incorrect command.");
	}
}

void CShapeMenu::CheckTriangleArguments(const ParametersList& parametersList)
{
	if ((parametersList.size() != 7 && parametersList.size() != 9))
	{
		throw std::invalid_argument("Incorrect amount arguments! Must will be 7 or 9!");
	}
}

void CShapeMenu::CheckRectangleArguments(const ParametersList& parametersList)
{
	if ((parametersList.size() != 5 && parametersList.size() != 7))
	{
		throw std::invalid_argument("Incorrect amount arguments! Must will be 5 or 7!");
	}
}

void CShapeMenu::CheckCircleArguments(const ParametersList& parametersList)
{
	if ((parametersList.size() != 4 && parametersList.size() != 6))
	{
		throw std::invalid_argument("Incorrect amount arguments! Must will be 4 or 6!");
	}
}

void CShapeMenu::CheckLineSegmentArguments(const ParametersList& parametersList)
{
	if ((parametersList.size() != 5 && parametersList.size() != 6))
	{
		throw std::invalid_argument("Incorrect amount arguments! Must will be 5 or 6!");
	}
}

double CShapeMenu::CheckShapeParameter(const std::string& parameter)
{
	std::size_t length;
	double point;
	try
	{
		point = std::stod(parameter, &length);
		if (length != parameter.length())
		{
			throw std::invalid_argument("Incorrect shape parameters! Non-numeric characters found!");
		}
		return point;
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Parameter is not a valid number!");
	}
}

void CShapeMenu::AddTriangle(const ParametersList& parametersList)
{
	CheckTriangleArguments(parametersList);

	SPoint vertex1 = { CheckShapeParameter(parametersList[1]), CheckShapeParameter(parametersList[2]) };
	SPoint vertex2 = { CheckShapeParameter(parametersList[3]), CheckShapeParameter(parametersList[4]) };
	SPoint vertex3 = { CheckShapeParameter(parametersList[5]), CheckShapeParameter(parametersList[6]) };

	std::string outlineColor = m_defaulOutlineColor;
	std::string fillColor = m_defaultFillColor;
	if (parametersList.size() == 9)
	{
		outlineColor = parametersList[7];
		fillColor = parametersList[8];
	}

	auto triangle = std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
	m_shapesList.push_back(triangle);
}

void CShapeMenu::AddRectangle(const ParametersList& parametersList)
{
	CheckRectangleArguments(parametersList);

	SPoint leftTop = { CheckShapeParameter(parametersList[1]), CheckShapeParameter(parametersList[2]) };
	SPoint rightBottom = { CheckShapeParameter(parametersList[3]), CheckShapeParameter(parametersList[4]) };

	std::string outlineColor = m_defaulOutlineColor;
	std::string fillColor = m_defaultFillColor;
	if (parametersList.size() == 7)
	{
		outlineColor = parametersList[5];
		fillColor = parametersList[6];
	}

	auto rectangle = std::make_shared<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);
	m_shapesList.push_back(rectangle);
}

void CShapeMenu::AddCircle(const ParametersList& parametersList)
{
	CheckCircleArguments(parametersList);

	SPoint center = { CheckShapeParameter(parametersList[1]), CheckShapeParameter(parametersList[2]) };
	double radius = CheckShapeParameter(parametersList[3]);
	if (radius < 0)
	{
		throw std::invalid_argument("Parameter #3 - \"radius\" must be non-negative!");
	}

	std::string outlineColor = m_defaulOutlineColor;
	std::string fillColor = m_defaultFillColor;
	if (parametersList.size() == 6)
	{
		outlineColor = parametersList[4];
		fillColor = parametersList[5];
	}

	auto circle = std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
	m_shapesList.push_back(circle);
}

void CShapeMenu::AddLineSegment(const ParametersList& parametersList)
{
	CheckLineSegmentArguments(parametersList);

	SPoint startPoint = { CheckShapeParameter(parametersList[1]), CheckShapeParameter(parametersList[2]) };
	SPoint endPoint = { stod(parametersList[3]), stod(parametersList[4]) };

	std::string outlineColor = m_defaulOutlineColor;
	if (parametersList.size() == 6)
	{
		outlineColor = parametersList[5];
	}

	auto lineSegment = std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
	m_shapesList.push_back(lineSegment);
}

void CShapeMenu::PrintShapeMinPerimeter()
{
	if (m_shapesList.empty())
	{
		std::cout << "Shape with small perimeter no found. The list of shapes is empty." << std::endl;
		return;
	}
	std::shared_ptr<IShape> shapeMinPerimeter = GetShapeMinPerimeter();
	if (shapeMinPerimeter == nullptr)
	{
		std::cout << "Shape with small perimeter no found." << std::endl;
	}
	else
	{
		std::cout << "Shape with small perimeter:\n"
				  << shapeMinPerimeter->ToString() << std::endl;
	}
}

std::shared_ptr<IShape> CShapeMenu::GetShapeMinPerimeter()
{
	std::shared_ptr<IShape> shapeMinPerimeter = nullptr;
	double minPerimeter = std::numeric_limits<double>::max();
	for (const auto& shape : m_shapesList)
	{
		double currentPerimeter = shape->GetPerimeter();
		if (currentPerimeter < minPerimeter)
		{
			minPerimeter = currentPerimeter;
			shapeMinPerimeter = shape;
		}
	}
	return shapeMinPerimeter;
}

void CShapeMenu::PrintShapeMaxArea()
{
	if (m_shapesList.empty())
	{
		std::cout << "Shape with large area no found. The list of shapes is empty." << std::endl;
		return;
	}
	std::shared_ptr<IShape> shapeMaxArea = GetShapeMaxArea();
	if (shapeMaxArea == nullptr)
	{
		std::cout << "Shape with large area no found." << std::endl;
	}
	else
	{
		std::cout << "Shape with large area:\n"
				  << shapeMaxArea->ToString() << std::endl;
	}
}

std::shared_ptr<IShape> CShapeMenu::GetShapeMaxArea()
{
	std::shared_ptr<IShape> shapeMaxArea = nullptr;
	double maxArea = std::numeric_limits<double>::lowest();
	for (const auto& shape : m_shapesList)
	{
		double currentArea = shape->GetArea();
		if (currentArea > maxArea)
		{
			maxArea = currentArea;
			shapeMaxArea = shape;
		}
	}
	return shapeMaxArea;
}

void CShapeMenu::PrintInfo() const
{
	for (const auto& shape : m_shapesList)
	{
		std::cout << shape->ToString() << std::endl;
	}
}