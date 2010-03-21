#pragma once

#include <math.h>

#include "Point.h"

//
// Ќецела€ точка
//
struct FPoint
{
	float x;
	float y;

	//
	//  онструктор из целой точки
	//
	FPoint(const Point& p)
		: x(float(p.x))
		, y(float(p.y))
	{
	}

	//
	// ѕокоординатный конструктор 
	//
	FPoint(float x_, float y_)
		: x(x_)
		, y(y_)
	{
	}

	//
	// ¬озвращает точку, повернутую на angle радиан против часовой стрелки
	// относительно начала координат
	//
	FPoint Rotate(float angle) {
		float x2 = x * cosf(angle) - y * sinf(angle);
		float y2 = x * sinf(angle) + y * cosf(angle);
		return FPoint(x2, y2);
	}

	FPoint& operator += (const FPoint& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	FPoint operator + (const FPoint& right) {
		return FPoint(*this) += right;
	}

	FPoint& operator -= (const FPoint& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	FPoint operator - (const FPoint& right) {
		return FPoint(*this) -= right;
	}
};
