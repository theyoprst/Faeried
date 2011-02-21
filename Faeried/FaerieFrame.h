#pragma once

#include <map>
#include "FPoint.h"

//
// �����, ��������������� ��������� ��� � ������� ������ �������
//
class FaerieFrame
{
public:

	typedef std::map<std::string, float> BonesDegrees;
		// ����������� ��� ����� - ���� �������� � ��������

	//
	// ������ �� Xml
	// 
	explicit FaerieFrame(Xml::Node* xn);

	//
	// ����������� (������������ ��� ������������)
	//
	FaerieFrame(const BonesDegrees& bonesDegrees, FPoint shift);

	//
	// ����������� �� ���������
	//
	FaerieFrame();

	//
	// ��������� Xml (��� ����������)
	//
	void FillXml(Xml::Document* document, Xml::Node* element);

	//
	// ������� ���� �������� ������
	//
	const BonesDegrees& GetBonesDegrees() const;

	//
	// ������� ��������
	//
	FPoint GetShift() const;

	//
	// ���������� ���� ������� �����
	//
	void SetBoneAngle(std::string boneName, int angleInDegrees);

	//
	// ���������� �����
	//
	void SetShift(FPoint shift);

	//
	// ������� ���� ������� �����
	//
	float GetBoneAngle(std::string boneName);

	//
	// ������� �����
	//
	FPoint GetShift();

private:

	BonesDegrees _bonesDegrees;
		// ������� ��������

	FPoint _shift;
		// ��������

};