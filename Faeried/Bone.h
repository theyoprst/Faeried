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
	// Передаем координату левой верхней точки родителя
	// и угол поворота родителя против часовой стрелки
	//
	void Draw(FPoint parentLeftTopCorner, float parentAngle);

	//
	// Возвращает кость под мышью; проверяет себя, затем детей.
	//
	Bone* GetBoneUnderMouse(Point p, FPoint parentLeftTopCorner, float parentAngle);

	//
	// Эту кость перетаскивают, обрабатываем вращение
	//
	void Drag(Point p);

	//
	// Эту кость отпустили, можно расслабиться
	//
	void FinishDragging();

	//
	// Вернуть угол в градусах
	//
	float GetAngleInDegrees();

	//
	// Установить позицию относительно родителя
	// (актуально только для корневой кости)
	//
	void SetInParentPos(FPoint pos);

	//
	// Вернуть позицию относительно родителя
	//
	FPoint GetInParentPos();

	//
	// Установить угол поворота в градусах
	//
	void SetAngleInDegrees(float angleInDegrees);

	//
	// Установить масштаб
	//
	static void SetScale(float newScale);

private:
	
	static float _scale;
		// масштаб

	std::string _name;
		// уникальное имя кости

	hgeSprite* _sprite;
		// спрайт (изображение) кости

	FPoint _inParentPosition;
		// позиция внутри родителя (относительно левого верхнего угла родителя)

	Point _rotationPoint;
		// точка вращения (относительно левого верхнего угла текстуры)

	HGE* _hge;
		// указатель на объект вывода

	typedef std::list<Bone*> Children;
	
	Children _children;
		// список детей; сюда же входит и родитель - для отрисовки в нужном порядке

	float _angle;
		// угол поворота в радианах против часовой стрелки

	enum {
		
		STATE_NORMAL,
			// обычное состояние кости

		STATE_ROTATING,
			// кость вращается

		STATE_MOVING,
			// кость движется

	} _state;
		// значит либо навели, либо таскают; в любом случае, посвечиваем зеленым

	FPoint _dragRotateCenter;
		// центр вращения при перетаскивании

	FPoint _dragRotatePoint1;
		// начальные координаты мыши при вращении

	float _dragAngle1;
		// начальные угол при вращении

	bool _isRoot;
		// корневая ли кость

	Point _dragInParentPosition;
		// сохраненная позиция относительно родителя перед перетаскиванием

	Point _dragMousePos;
		// сохраненная позиция мыши перед перетаскиванием

	bool _doNotLight;
		// не подсвечивать

	void SetNotActiveRecursively();

};
