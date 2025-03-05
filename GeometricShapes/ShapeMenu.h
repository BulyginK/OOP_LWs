#pragma once
#include "Circle.h"
#include "IShape.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class CShapeMenu
{
public:
	void ReadShape(std::string& commandLine); // по констатной ссылке - в функции использовать новую переменную
	void PrintShapeMinPerimeter();
	void PrintShapeMaxArea();
	void PrintInfo() const;

private:
	using ShapesList = std::vector<std::shared_ptr<IShape>>;
	using ParametersList = std::vector<std::string>;

	void AddTriangle(const ParametersList& parametersList);
	void AddRectangle(const ParametersList& parametersList);
	void AddCircle(const ParametersList& parametersList);
	void AddLineSegment(const ParametersList& parametersList);

	void CheckTriangleArguments(const ParametersList& parametersList);
	void CheckRectangleArguments(const ParametersList& parametersList);
	void CheckCircleArguments(const ParametersList& parametersList);
	void CheckLineSegmentArguments(const ParametersList& parametersList);

	double CheckShapeParameter(const std::string& parameter);

	std::shared_ptr<IShape> GetShapeMinPerimeter();
	std::shared_ptr<IShape> GetShapeMaxArea();

	ShapesList m_shapesList;
	std::string m_defaulOutlineColor = "000000";
	std::string m_defaultFillColor = "ffffff";
};