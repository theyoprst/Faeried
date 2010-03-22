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
	// ����������� �� ���������
	//
	FPoint()
		: x(0.0f)
		, y(0.0f)
	{
	}

	//
	// ���������� �����, ���������� �� angle ������ �� ������� �������
	// ������������ ������ ���������.
	// �� ����� ���� (�������������), ����� ��������� ������ ������� �������,
	// �� ��� ��� ��� Oy ���������� ����, �� ��������� �������� �������� �����������.
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
	// ������� ����� �� angle ������ ������ ������� ������� (���������)
	//
	FPoint RotateCounterclockwise(float angle) {
		return RotateClockwise(-angle);
	}

	//
	// ���������� ���� �������� ������� ������������ Ox �� ������� �������
	// (���������)
	//
	float GetAngle() {
		return atan2f(y, x);
	}

	//
	// ���������� ������������ �� ������� �������
	// ���� �� ����� ������� �� ������� (p2)
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
	// ���������� ��� ��������� ����� �����
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
