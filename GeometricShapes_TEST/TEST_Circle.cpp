#include "stdafx.h"

#include "../GeometricShapes/Circle.h"

struct Circle_
{
	const SPoint center = { 0, 0 };
	const double radius = 10;
	const std::string outlineColor = "ff0000";
	const std::string fillColor = "00ff00";

	const CCircle �ircle;
	Circle_()
		: �ircle(center, radius, outlineColor, fillColor)
	{
	}
};

// ����
BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)
	// ����� ����� � ������������
	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK_EQUAL(�ircle.GetCenter().x, 0);
		BOOST_CHECK_EQUAL(�ircle.GetCenter().x, 0);
	}
	// ����� ������ = 10
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(�ircle.GetRadius(), 10);
	}
	// ����� ������� = 314 (����������)
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(�ircle.GetArea()), 314);
	}
	// ����� �������� = 62 (����������)
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(�ircle.GetPerimeter()), 62);
	}
	// ����� ���� ������� ff0000
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(�ircle.GetOutlineColor(), "ff0000");
	}
	// ����� ���� ������� ���������� ������� 00ff00
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(�ircle.GetFillColor(), "00ff00");
	}
	// ����� ������ �������� � ���� ������
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Circle:\n"
				   "\tarea = 314.16\n"
				   "\tperimeter = 62.83\n"
				   "\toutline color = #ff0000\n"
				   "\tfill color = #00ff00\n"
				   "\tCenterPoint(0.00, 0.00)\n"
				   "\tradius = 10.00\n";
		BOOST_CHECK_EQUAL(�ircle.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()


// ����� �� �������� ������� � ���������