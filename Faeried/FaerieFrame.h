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

	//
	// Установить угол наклона кости
	//
	void SetBoneAngle(std::string boneName, int angleInDegrees);

	//
	// Установить сдвиг
	//
	void SetShift(FPoint shift);

	//
	// Вернуть угол наклона кости
	//
	float GetBoneAngle(std::string boneName);

	//
	// Вернуть сдвиг
	//
	FPoint GetShift();

private:

	BonesDegrees _bonesDegrees;
		// градусы поворота

	FPoint _shift;
		// смещение

};