#pragma once

#include <map>
#include "FPoint.h"

//
// Класс, инкапсулирующий положение феи в текущий момент времени
//
class FaerieFrame
{
public:

	typedef std::map<std::string, float> BonesDegrees;
		// отображение имя кости - угол поворота в градусах

	//
	// Чтение из Xml
	// 
	explicit FaerieFrame(Xml::Node* xn);

	//
	// Конструктор (используется при интерполяции)
	//
	FaerieFrame(const BonesDegrees& bonesDegrees, FPoint shift);

	//
	// Конструктор по умолчанию
	//
	FaerieFrame();

	//
	// Заполнить Xml (для сохранения)
	//
	void FillXml(Xml::Document* document, Xml::Node* element);

	//
	// Вернуть углы поворота костей
	//
	const BonesDegrees& GetBonesDegrees() const;

	//
	// Вернуть смещение
	//
	FPoint GetShift() const;

private:

	BonesDegrees _bonesDegrees;
		// градусы поворота

	FPoint _shift;
		// смещение

};