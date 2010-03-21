#pragma once

#include <math.h>

#include "Point.h"

//
// ������� �����
//
struct FPoint
{
	float x;
	float y;

	//
	// ����������� �� ����� �����
	//
	FPoint(const Point& p)
		: x(float(p.x))
		, y(float(p.y))
	{
	}

	//
	// �������������� ����������� 
	//
	FPoint(float x_, float y_)
		: x(x_)
		, y(y_)
	{
	}

	//
	// ���������� �����, ���������� �� angle ������ �� ������� �������
	// ������������ ������ ���������.
	// �� ����� ���� (�������������), ����� ��������� ������ ������� �������,
	// �� ��� ��� ��� Oy ���������� ����, �� ��������� �������� �������� �����������.
	//
	FPoint RotateClockwise(float angle) {
		float x2 = x * cosf(angle) - y * sinf(angle);
		float y2 = x * sinf(angle) + y * cosf(angle);
		return FPoint(x2, y2);
	}

	//
	// ������� ����� �� angle ������ ������ ������� ������� (���������)
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
