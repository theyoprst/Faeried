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
	// ¬озвращает точку, повернутую на angle радиан по часовой стрелке
	// относительно начала координат.
	// Ќа самом деле (математически), точка вращаетс€ против часовой стрелки,
	// но так как ось Oy направлена вниз, то визуально вращение измен€ет направление.
	//
	FPoint RotateClockwise(float angle) {
		float x2 = x * cosf(angle) - y * sinf(angle);
		float y2 = x * sinf(angle) + y * cosf(angle);
		return FPoint(x2, y2);
	}

	//
	// ¬ращает точку на angle радиан против часовой стрелки (визуально)
	//
	FPoint RotateCounterclockwise(float angle) {
		return RotateClockwise(-angle);
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
