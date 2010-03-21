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
// Класс кости
//
class Bone
	: public QObject
{
	Q_OBJECT

public:
	
	//
	// Конструктор
	//
	Bone(HGE* hge, Xml::Node* boneXml, BonesMap* bonesMap);

	//
	// Отрисовать поддерево костей, начиная с этой
	//
	//
	void Draw(FPoint parentLeftTopCorner, float parentAngle);

public slots:
	
	//
	// Установить угол поворота в градусах
	//
	void SetAngleInDegrees(int angleInDegrees);

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

	float _angle;
		// угол поворота в радианах (против часовой или по часовой?)
};
