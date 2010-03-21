#pragma once

#include "M.h"
#include "Xml.h"

//
// Точка на плоскости
//
struct Point
{
	int x;
	int y;

	//
	// Конструктор
	//
	Point(int x_, int y_)
		: x(x_)
		, y(y_)
	{
	}

	//
	// Конструктор чтения точки из xml
	//
	Point(Xml::Node* xml) {
		assert(xml->first_attribute("x") != NULL);
		assert(xml->first_attribute("y") != NULL);
		x = Math::ParseInt(xml->first_attribute("x")->value());
		y = Math::ParseInt(xml->first_attribute("y")->value());
	}

	//
	// Оператор += для точки
	//
	Point& operator +=(const Point& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	//
	// Оператор + для точки.
	// См http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html
	//
	const Point operator + (const Point& right) {
		return Point(*this) += right;
	}

	//
	// Оператор -= для точки
	//
	Point& operator -=(const Point& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	//
	// Оператор + для точки.
	//
	const Point operator - (const Point& right) {
		return Point(*this) -= right;
	}

	Point operator -() {
		return Point(-x, -y);
	}
};
