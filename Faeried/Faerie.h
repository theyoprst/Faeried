#pragma once

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

private:

	Bone* _rootBone;
};
