#pragma once

#include <list>
#include <string>
#include <QtCore/QObject>

#include "FPoint.h"
#include "Point.h"
#include "Xml.h"

class HGE;
class hgeSprite;
class BonesMap;

//
// ����� �����
//
class Bone
	: public QObject
{
	Q_OBJECT

public:
	
	//
	// �����������
	//
	Bone(HGE* hge, Xml::Node* boneXml, BonesMap* bonesMap);

	//
	// ���������� ��������� ������, ������� � ����
	// �������� ���������� ����� ������� ����� ��������
	// � ���� �������� �������� ������ ������� �������
	//
	void Draw(FPoint parentLeftTopCorner, float parentAngle);

	//
	// ���������� ����� ��� �����; ��������� ����, ����� �����.
	//
	Bone* GetBoneUnderMouse(Point p, FPoint parentLeftTopCorner, float parentAngle);

	//
	// ��� ����� �������������, ������������ ��������
	//
	void Drag(Point p);

	//
	// ��� ����� ���������, ����� ������������
	//
	void FinishDragging();

public slots:
	
	//
	// ���������� ���� �������� � ��������
	//
	void SetAngleInDegrees(int angleInDegrees);

signals:

	//
	// ������ ��������� ����
	//
	void AngleInDegreesChanged(int newAngle);

private:
	
	std::string _name;
		// ���������� ��� �����

	hgeSprite* _sprite;
		// ������ (�����������) �����

	Point _inParentPosition;
		// ������� ������ �������� (������������ ������ �������� ���� ��������)

	Point _rotationPoint;
		// ����� �������� (������������ ������ �������� ���� ��������)

	HGE* _hge;
		// ��������� �� ������ ������

	typedef std::list<Bone*> Children;
	
	Children _children;
		// ������� �����

	float _angle;
		// ���� �������� � �������� ������ ������� �������

	bool _isActive;
		// ������ ���� ������, ���� �������; � ����� ������, ����������� �������

	FPoint _dragRotateCenter;
		// ����� �������� ��� ��������������

	FPoint _dragRotatePoint1;
		// ��������� ���������� ���� ��� ��������

	float _dragAngle1;
		// ��������� ���� ��� ��������

	void SetNotActiveRecursively();
};
