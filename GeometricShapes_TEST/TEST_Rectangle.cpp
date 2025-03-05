#include "stdafx.h"

#include "../GeometricShapes/Rectangle.h"

struct Rectangle_
{
	const SPoint leftTop = { 0, 6 };
	const SPoint rightBottom = { 5, 0 };
	const std::string outlineColor = "ff0000";
	const std::string fillColor = "00ff00";

	const CRectangle rectangle;
	Rectangle_()
		: rectangle(leftTop, rightBottom, outlineColor, fillColor)
	{
	}
};

// �������������
BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
	// ����� ��������� ����� ������� ������� (0,6)
	BOOST_AUTO_TEST_CASE(left_top_vertex_has_a_position)
	{
		BOOST_CHECK_EQUAL(rectangle.GetLeftTop().x, 0);
		BOOST_CHECK_EQUAL(rectangle.GetLeftTop().y, 6);
	}
	// ����� ��������� ������ ������ ������� (5,0)
	BOOST_AUTO_TEST_CASE(right_bottom_left_top_vertex_has_a_position)
	{
		BOOST_CHECK_EQUAL(rectangle.GetRightBottom().x, 5);
		BOOST_CHECK_EQUAL(rectangle.GetRightBottom().y, 0);
	}
	// ����� ������ = 5
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(rectangle.GetWidth(), 5);
	}
	// ����� ������ = 6
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(rectangle.GetHeight(), 6);
	}
	// ����� ������� = 30 (����������)
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(rectangle.GetArea()), 30);
	}
	// ����� �������� = 22 (����������)
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(rectangle.GetPerimeter()), 22);
	}
	// ����� ���� ������� ff0000
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), "ff0000");
	}
	// ����� ���� ������� ���������� ������� 00ff00
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), "00ff00");
	}
	// ����� ������ �������� � ���� ������
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Rectangle:\n"
				   "\tarea = 30.00\n"
				   "\tperimeter = 22.00\n"
				   "\toutline color = #ff0000\n"
				   "\tfill color = #00ff00\n"
				   "\tLeftTopPoint(0.00, 6.00)\n"
				   "\tRightBottomPoint(5.00, 0.00)\n";
		BOOST_CHECK_EQUAL(rectangle.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()