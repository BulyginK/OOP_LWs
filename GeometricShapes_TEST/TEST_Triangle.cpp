#include "stdafx.h"

#include "../GeometricShapes/Triangle.h"

struct Triangle_
{
	const SPoint Vertex1 = { 1, 1 };
	const SPoint Vertex2 = { 11, 1 };
	const SPoint Vertex3 = { 1, 11 };
	const std::string outlineColor = "ff0000";
	const std::string fillColor = "00ff00";

	const CTriangle triangle;
	Triangle_()
		: triangle(Vertex1, Vertex2, Vertex3, outlineColor, fillColor)
	{
	}
};
// Треугольник
BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
	// имеет координты первой вершины (1,1)
	BOOST_AUTO_TEST_CASE(first_vertex_of_triangle_has_a_position)
	{
		BOOST_CHECK_EQUAL(triangle.GetVertex1().x, Vertex1.x);
		BOOST_CHECK_EQUAL(triangle.GetVertex1().y, Vertex1.y);
	}
	// имеет координты второй вершины (11,1)
	BOOST_AUTO_TEST_CASE(second_vertex_of_triangle_has_a_position)
	{
		BOOST_CHECK_EQUAL(triangle.GetVertex2().x, Vertex2.x);
		BOOST_CHECK_EQUAL(triangle.GetVertex2().y, Vertex2.y);
	}
	// имеет координты третьей вершины (1,11)
	BOOST_AUTO_TEST_CASE(third_vertex_of_triangle_has_a_position)
	{
		BOOST_CHECK_EQUAL(triangle.GetVertex3().x, Vertex3.x);
		BOOST_CHECK_EQUAL(triangle.GetVertex3().y, Vertex3.y);
	}
	// имеет площадь = 50 (округленно)
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(triangle.GetArea()), 50);
	}
	// имеет периметр = 34 (округленно) 
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(triangle.GetPerimeter()), 34);
	}
	// имеет цвет обводки ff0000
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки внутренней области 00ff00
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), "00ff00");
	}
	// имеет данное описание в виде строки
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Triangle:\n"
				   "\tarea = 50.00\n"
				   "\tperimeter = 34.14\n"
				   "\toutline color = #ff0000\n"
				   "\tfill color = #00ff00\n"
				   "\tVertex1(1.00, 1.00)\n"
				   "\tVertex2(11.00, 1.00)\n"
				   "\tVertex3(1.00, 11.00)\n";
		BOOST_CHECK_EQUAL(triangle.ToString(), str);
	}
BOOST_AUTO_TEST_SUITE_END()