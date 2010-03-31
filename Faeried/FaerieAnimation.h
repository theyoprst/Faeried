#pragma once

#include <list>

#include "FaerieFrame.h"
#include "Spline.h"

class FaerieFrame;

//
// ����� �������� ���
//
class FaerieAnimation
{

public:
	
	//
	// ������ �� XML
	//
	explicit FaerieAnimation(Xml::Node* xn);

	//
	// �������� �������� � ������������ ������
	//
	explicit FaerieAnimation(std::string name);

	//
	// ������� ���� �������� �� ���������������� ������� t
	//
	FaerieFrame GetFrame(float t);

	//
	// ��������� Xml-������� ��������
	//
	void FillXml(Xml::Document* document, Xml::Node* element);

	//
	// ������� ��� ��������
	//
	std::string GetName();

	//
	// ������� ����� ��������
	//
	float GetTime();

	//
	// ���������� ����� ��������
	//
	void SetTime(float time);

	//
	// ������� ���������� ������ ��������
	//
	int GetFramesNumber();

	//
	// ����������� ���� ����� frameNumber
	//
	void CloneFrame(int frameNumber);

	//
	// ������� ���� ����� frameNumber
	//
	void DeleteFrame(int frameNumber);

private:

	typedef std::list<FaerieFrame> KeyFrames;

	KeyFrames _keyFrames;
		// ������ �������� ������

	typedef std::map<std::string, SplinePath> AngleSplines;

	AngleSplines _angleSplines;
		// ������� �����

	SplinePath _xSpline;
		// ������ x

	SplinePath _ySpline;
		// ������ y

	std::string _name;
		// ��� ��������

	float _time;
		// ����� ��������

	//
	// ������� ������� ��������
	//
	void CreateAnimationSplines();

	//
	// �������� ����� � �������
	//
	void AddFrameToSpline(size_t frameNumber, const FaerieFrame& frame);
};
