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
	//  онструктор по умолчанию
	//
	FPoint()
		: x(0.0f)
		, y(0.0f)
	{
	}

	//
	// ¬озвращает точку, повернутую на angle радиан по часовой стрелке
	// относительно начала координат.
	// Ќа самом деле (математически), точка вращаетс€ против часовой стрелки,
	// но так как ось Oy направлена вниз, то визуально вращение измен€ет направление.
	//
	FPoint RotateClockwise(float angle) {
		float c = cosf(angle);
		float s = sinf(angle);
		return FPoint(
			x * c - y * s,
			x * s + y * c
		);
	}

	//
	// ¬ращает точку на angle радиан против часовой стрелки (визуально)
	//
	FPoint RotateCounterclockwise(float angle) {
		return RotateClockwise(-angle);
	}

	//
	// ¬озвращает угол поворота вектора относительно Ox по часовой стрелке
	// (визуально)
	//
	float GetAngle() {
		return atan2f(y, x);
	}

	//
	// ¬озвращает направленный по часовой стрелке
	// угол от этого вектора до другого (p2)
	//
	float GetDirectedAngleTo(FPoint p2) {
		float angle = p2.GetAngle() - this->GetAngle();
		if (angle < -Math::PI) {
			return angle + Math::PI * 2;
		} else if (angle > Math::PI) {
			return angle - Math::PI * 2;
		} else {
			return angle;
		}
	}

	//
	// ќкругление дл€ ближайшей целой точки
	//
	Point Round() {
		return Point(Math::Round(x), Math::Round(y));
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

	bool operator == (const FPoint& right) {
		return x == right.x && y == right.y;
	}

	bool operator != (const FPoint& right) {
		return !(*this == right);
	}

};
