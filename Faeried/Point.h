#pragma once

#include "Int.h"
#include "Xml.h"

#include <QtCore/QPoint>

//
// ����� �� ���������
//
struct Point
{
	int x;
	int y;

	//
	// �����������
	//
	Point(int x_, int y_)
		: x(x_)
		, y(y_)
	{
	}

	//
	// ����������� ������ ����� �� xml
	//
	explicit Point(Xml::Node* xml) {
		assert(xml->first_attribute("x") != NULL);
		assert(xml->first_attribute("y") != NULL);
		x = Int::Parse(xml->first_attribute("x")->value());
		y = Int::Parse(xml->first_attribute("y")->value());
	}

	//
	// ����������� �� QPoint-�
	//
	explicit Point(const QPoint& p)
		: x(p.x())
		, y(p.y())
	{
	}

	//
	// ����������� �� ���������
	//
	Point()
		: x(0)
		, y(0)
	{
	}

	//
	// �������� += ��� �����
	//
	Point& operator +=(const Point& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	//
	// �������� + ��� �����.
	// �� http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html
	//
	Point operator + (const Point& right) {
		return Point(*this) += right;
	}

	//
	// �������� -= ��� �����
	//
	Point& operator -=(const Point& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	//
	// �������� - ��� �����.
	//
	Point operator - (const Point& right) {
		return Point(*this) -= right;
	}

	Point operator -() {
		return Point(-x, -y);
	}
};
