#pragma once

#include <QtCore/QObject>

#include "BonesMap.h"

class Bone;
class FaerieAnimation;
class hgeSprite;
class HGE;

#include "FaerieFrame.h"
#include "FPoint.h"
#include "Point.h"

//
// Собственно фея
//
class Faerie
	: public QObject
{

	Q_OBJECT

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

	FPoint _shift;
		// сдвиг

	float _animationTimer;
		// таймер анимации

	FaerieAnimation* _animation;
		// текущая анимация (в состоянии STATE_ANIMATION)

	enum {

		STATE_NOFRAME,
			// нет никакого кадра, ничего не рисуем

		STATE_SINGLE_FRAME,
			// отрисовываем статический кадр и ждем кликов
		
		STATE_DRAGGING_BONE,
			// юзер тащит кость мышью

		STATE_ANIMATION,
			// проигрывается анимация

	} _state;
		// текущее состояние

public slots:
	
	//
	// Слот "изменился кадр из гуи"
	//
	void GuiChangedFrame(FaerieFrame frame);

	//
	// Нужно ли показывать фею
	//
	void SlotShowFaerie(bool);

	//
	// Нажали на кнопку начать анимацию
	//
	void StartAnimationSlot(FaerieAnimation* animation);

	//
	// Нажали на кнопку закончить анимацию
	//
	void StopAnimationSlot();

signals:

	//
	// Сигнал "изменился кадр через фею"
	//
	void FaerieChangedFrameSignal(FaerieFrame frame);

private:

	//
	// Создать фрейм из текущего положения костей
	//
	FaerieFrame CreateFrame();
};
