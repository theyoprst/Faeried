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

	//
	// ������� ���� � ��������
	//
	float GetAngleInDegrees();

	//
	// ���������� ������� ������������ ��������
	// (��������� ������ ��� �������� �����)
	//
	void SetInParentPos(FPoint pos);

	//
	// ������� ������� ������������ ��������
	//
	FPoint GetInParentPos();

	//
	// ���������� ���� �������� � ��������
	//
	void SetAngleInDegrees(float angleInDegrees);

	//
	// ���������� �������
	//
	static void SetScale(float newScale);

private:
	
	static float _scale;
		// �������

	std::string _name;
		// ���������� ��� �����

	hgeSprite* _sprite;
		// ������ (�����������) �����

	FPoint _inParentPosition;
		// ������� ������ �������� (������������ ������ �������� ���� ��������)

	Point _rotationPoint;
		// ����� �������� (������������ ������ �������� ���� ��������)

	HGE* _hge;
		// ��������� �� ������ ������

	typedef std::list<Bone*> Children;
	
	Children _children;
		// ������ �����; ���� �� ������ � �������� - ��� ��������� � ������ �������

	float _angle;
		// ���� �������� � �������� ������ ������� �������

	enum {
		
		STATE_NORMAL,
			// ������� ��������� �����

		STATE_ROTATING,
			// ����� ���������

		STATE_MOVING,
			// ����� ��������

	} _state;
		// ������ ���� ������, ���� �������; � ����� ������, ����������� �������

	FPoint _dragRotateCenter;
		// ����� �������� ��� ��������������

	FPoint _dragRotatePoint1;
		// ��������� ���������� ���� ��� ��������

	float _dragAngle1;
		// ��������� ���� ��� ��������

	bool _isRoot;
		// �������� �� �����

	Point _dragInParentPosition;
		// ����������� ������� ������������ �������� ����� ���������������

	Point _dragMousePos;
		// ����������� ������� ���� ����� ���������������

	bool _doNotLight;
		// �� ������������

	void SetNotActiveRecursively();

};
