#pragma once

#include <math.h>

#include "M.h"
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
	FPoint RotateClockwise(float angle) const {
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
	FPoint RotateCounterclockwise(float angle) const {
		return RotateClockwise(-angle);
	}

	//
	// ���������� ���� �������� ������� ������������ Ox �� ������� �������
	// (���������)
	//
	float GetAngle() const {
		return atan2f(y, x);
	}

	//
	// ���������� ������������ �� ������� �������
	// ���� �� ����� ������� �� ������� (p2)
	//
	float GetDirectedAngleTo(FPoint p2) const {
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
	Point Round() const {
		return Point(Math::Round(x), Math::Round(y));
	}

	FPoint& operator += (const FPoint& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	FPoint operator + (const FPoint& right) const {
		return FPoint(*this) += right;
	}

	FPoint& operator -= (const FPoint& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	FPoint operator - (const FPoint& right) const {
		return FPoint(*this) -= right;
	}

	bool operator == (const FPoint& right) const {
		return x == right.x && y == right.y;
	}

	bool operator != (const FPoint& right) const {
		return !(*this == right);
	}

	FPoint Scale(float factor) const {
		return FPoint(x * factor, y * factor);
	}

	FPoint Divide(float divisor) const {
		assert(divisor != 0.0f);
		return Scale(1.0f / divisor);
	}
};

inline FPoint operator * (const FPoint& p, float scale) {
	return p.Scale(scale);
}

inline FPoint operator * (float scale, const FPoint& p) {
	return p.Scale(scale);
}

inline FPoint operator / (const FPoint& p, float divisor) {
	return p.Divide(divisor);
}