#include "stdafx.h"

#include "../GeometricShapes/Circle.h"

struct Circle_
{
	const SPoint center = { 0, 0 };
	const double radius = 10;
	const std::string outlineColor = "ff0000";
	const std::string fillColor = "00ff00";

	const CCircle сircle;
	Circle_()
		: сircle(center, radius, outlineColor, fillColor)
	{
	}
};

// Круг
BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)
	// имеет центр в координатами
	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK_EQUAL(сircle.GetCenter().x, 0);
		BOOST_CHECK_EQUAL(сircle.GetCenter().x, 0);
	}
	// имеет радиус = 10
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(сircle.GetRadius(), 10);
	}
	// имеет площадь = 314 (округленно)
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(сircle.GetArea()), 314);
	}
	// имеет периметр = 62 (округленно)
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(сircle.GetPerimeter()), 62);
	}
	// имеет цвет обводки ff0000
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(сircle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки внутренней области 00ff00
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(сircle.GetFillColor(), "00ff00");
	}
	// имеет данное описание в виде строки
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Circle:\n"
				   "\tarea = 314.16\n"
				   "\tperimeter = 62.83\n"
				   "\toutline color = #ff0000\n"
				   "\tfill color = #00ff00\n"
				   "\tCenterPoint(0.00, 0.00)\n"
				   "\tradius = 10.00\n";
		BOOST_CHECK_EQUAL(сircle.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()


// тесты на проверку площади и периметра