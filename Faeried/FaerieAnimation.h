#pragma once

#include <list>

#include "FaerieFrame.h"
#include "Spline.h"

class FaerieFrame;

//
// Класс анимации феи
//
class FaerieAnimation
{

public:
	
	//
	// Чтение из XML
	//
	explicit FaerieAnimation(Xml::Node* xn);

	//
	// Создание анимации с единственным кадром
	//
	explicit FaerieAnimation(std::string name);

	//
	// Вернуть кадр анимации по нормализованному времени t
	//
	FaerieFrame GetFrame(float t);

	//
	// Заполнить Xml-элемент анимации
	//
	void FillXml(Xml::Document* document, Xml::Node* element);

	//
	// Вернуть имя анимации
	//
	std::string GetName();

	//
	// Вернуть время анимации
	//
	float GetTime();

	//
	// Установить время анимации
	//
	void SetTime(float time);

	//
	// Вернуть количество кадров анимации
	//
	int GetFramesNumber();

	//
	// Клонировать кадр номер frameNumber
	//
	void CloneFrame(int frameNumber);

	//
	// Удалить кадр номер frameNumber
	//
	void DeleteFrame(int frameNumber);

private:

	typedef std::list<FaerieFrame> KeyFrames;

	KeyFrames _keyFrames;
		// список ключевых кадров

	typedef std::map<std::string, SplinePath> AngleSplines;

	AngleSplines _angleSplines;
		// сплайны углов

	SplinePath _xSpline;
		// сплайн x

	SplinePath _ySpline;
		// сплайн y

	std::string _name;
		// имя анимации

	float _time;
		// время анимации

	//
	// Создать сплайны анимации
	//
	void CreateAnimationSplines();

	//
	// Добавить фрейм к сплайну
	//
	void AddFrameToSpline(size_t frameNumber, const FaerieFrame& frame);
};
