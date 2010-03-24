#pragma once

#include "BonesMap.h"

class hgeSprite;
class HGE;
class Bone;

#include "Point.h"

//
// Собственно фея
//
class Faerie {

public:
	
	//
	// Конструктор
	//
	explicit Faerie(HGE *hge);

	//
	// Отрисовка
	//
	void Draw(int x, int y);

	//
	// Обновить фею
	//
	void Update(float dt);

	//
	// Вернуть кость по ее имени
	//
	Bone* GetBoneByName(std::string boneName);

	//
	// Двинули мышью
	//
	void OnMouseMove(Point p);

	//
	// Кликнули мышью
	//
	void OnLeftMouseDown(Point p);

	//
	// Отпустили левую кнопку мыши
	//
	void OnLeftMouseUp(Point p);

private:

	Bone* _rootBone;
		// корневая кость (поясница)

	BonesMap _bonesMap;
		// отображение "имя - указатель на кость"

	Bone* _draggingBone;
		// перетаскиваемая кость

	enum {
		
		STATE_WAITING,
			// состояние ожидания
		
		STATE_DRAGGING_BONE,
			// юзер тащит кость мышью

	} _state;
		// текущее состояниеы
};
