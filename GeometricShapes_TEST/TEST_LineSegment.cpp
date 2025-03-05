#include "stdafx.h"

#include "../GeometricShapes/LineSegment.h"

struct LineSegment_
{
	const SPoint startPoint = { 0, 0 };
	const SPoint endPoint = { 3, 4 };
	const std::string outlineColor = "ff0000";

	const CLineSegment lineSegment;
	LineSegment_()
		: lineSegment(startPoint, endPoint, outlineColor)
	{
	}
};

// �������
BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegment_)
	// ����� ��������� ������ �����
	BOOST_AUTO_TEST_CASE(has_a_start_point)
	{
		BOOST_CHECK_EQUAL(lineSegment.GetStartPoint().x, 0);
		BOOST_CHECK_EQUAL(lineSegment.GetStartPoint().y, 0);
	}
	// ����� ��������� ������ �����
	BOOST_AUTO_TEST_CASE(has_a_end_point)
	{
		BOOST_CHECK_EQUAL(lineSegment.GetEndPoint().x, 3);
		BOOST_CHECK_EQUAL(lineSegment.GetEndPoint().y, 4);
	}
	// ������� = 0
	BOOST_AUTO_TEST_CASE(line_has_zero_area)
	{
		BOOST_CHECK_EQUAL(lineSegment.GetArea(), 0);
	}
	// �������� ����� �����
	BOOST_AUTO_TEST_CASE(perimeter_is_equal_length_of_segment)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(lineSegment.GetPerimeter()), 5);
	}
	// ����� ���� = ff0000
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(lineSegment.GetOutlineColor(), "ff0000");
	}
	// ����� ������ �������� � ���� ������
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "LineSegment:\n"
				   "\tarea = 0.00\n"
				   "\tperimeter = 5.00\n"
				   "\toutline color = #ff0000\n"
				   "\tStartPoint(0.00, 0.00)\n"
				   "\tEndPoint(3.00, 4.00)\n";
		BOOST_CHECK_EQUAL(lineSegment.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()