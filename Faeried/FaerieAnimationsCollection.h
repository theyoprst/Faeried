#pragma once

#include <map>

#include "FaerieAnimation.h"
#include "types.h"

//
// Класс-набор анимаций.
// Отвечает за чтение и запись анимаций на диск
//
class FaerieAnimationsCollection
{
public:
	
	//
	// Чтение с диска
	//
	FaerieAnimationsCollection(std::string filename);

	//
	// Запись на диск
	//
	void Store();

	//
	// Вернуть указатель на анимацию;
	// Анимация с таким именем обязана существовать
	//
	FaerieAnimation* GetAnimation(std::string animationName);

	//
	// Есть ли такая анимация в коллекции
	//
	bool HasAnimation(std::string animationName);

	//
	// Добавить анимацию в коллекцию
	//
	void AddAnimation(FaerieAnimation* animation);

	//
	// Удалить анимацию из коллекции
	//
	void DeleteAnimation(std::string animationName);

	//
	// Вернуть список имен анимаций
	//
	StringVector GetAnimationsNames();

private:

	typedef std::map<std::string, FaerieAnimation*> MapAnimations;

	MapAnimations _mapAnimations;
		// отображение "имя - анимация"

	std::string _filename;
		// имя файла, запоминаем чтобы сохранить туда же
};
