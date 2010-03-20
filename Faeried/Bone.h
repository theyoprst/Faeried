#pragma once

#include <list>
#include <string>

#include "Point.h"

namespace rapidxml {
	template<typename Ch> class xml_node;
}
class HGE;
class hgeSprite;

//
// ����� �����
//
class Bone {

public:
	
	//
	// �����������
	//
	Bone(HGE* hge, rapidxml::xml_node<char>* boneXml);

	//
	// ���������� ��������� ������, ������� � ����
	//
	//
	void Draw(Point parentLeftTopCorner);

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

};
