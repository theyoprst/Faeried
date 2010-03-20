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
// Класс кости
//
class Bone {

public:
	
	//
	// Конструктор
	//
	Bone(HGE* hge, rapidxml::xml_node<char>* boneXml);

	//
	// Отрисовать поддерево костей, начиная с этой
	//
	//
	void Draw(Point parentLeftTopCorner);

private:
	
	std::string _name;
		// уникальное имя кости

	hgeSprite* _sprite;
		// спрайт (изображение) кости

	Point _inParentPosition;
		// позиция внутри родителя (относительно левого верхнего угла)

	Point _rotationPoint;
		// точка вращения

	typedef std::list<Bone*> Children;
	
	Children _children;
		// детские кости

};
