#pragma once

#include "BonesMap.h"

class hgeSprite;
class HGE;
class Bone;

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
	void Draw();

	//
	// Обновить фею
	//
	void Update(float dt);

	//
	// Вернуть кость по ее имени
	//
	Bone* GetBoneByName(std::string boneName);

private:

	Bone* _rootBone;

	BonesMap _bonesMap;
		// отображение "имя - указатель на кость"
};
