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
	//
	//
	void Draw(FPoint parentLeftTopCorner, float parentAngle);

public slots:
	
	//
	// ���������� ���� �������� � ��������
	//
	void SetAngleInDegrees(int angleInDegrees);

private:
	
	std::string _name;
		// ���������� ��� �����

	hgeSprite* _sprite;
		// ������ (�����������) �����

	Point _inParentPosition;
		// ������� ������ �������� (������������ ������ �������� ����)

	Point _rotationPoint;
		// ����� ��������

	typedef std::list<Bone*> Children;
	
	Children _children;
		// ������� �����

	float _angle;
		// ���� �������� � �������� (������ ������� ��� �� �������?)
};
