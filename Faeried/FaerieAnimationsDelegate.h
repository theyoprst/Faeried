#pragma once

#include <QtCore/QObject>

#include "FaerieFrame.h"
class FaerieAnimation;
class FaerieAnimationsCollection;

//
// Класс, непосредственно реагирующий на действия пользователей и
// изменяющий в соответствии с этими действиями анимации
//
class FaerieAnimationsDelegate
	: public QObject
{

	Q_OBJECT

public:

	//
	// Конструктор
	//
	explicit FaerieAnimationsDelegate(FaerieAnimationsCollection* collection);

	//
	// Есть ли анимация с таким именем
	//
	bool HasAnimation(std::string name);

	//
	// Добавить анимацию с таким именем
	//
	void AddAnimation(std::string name);

	//
	// Удалить текущую анимацию
	//
	void DeleteCurrentAnimation();

	//
	// Инициализировать вид редактора
	//
	void InitView();

signals:

	//
	// Событие, вызываемое, когда нужно инициализировать список анимаций
	//
	void SetAnimationsList(const QStringList& list);

	//
	// Событие установить список кадров
	//
	void SetFramesList(const QStringList& list);

	//
	// Событие выбрали анимацию / анимация не выбрана
	//
	void AnimationIsSelected(bool isAnimationSelected);

	//
	// Событие инициализировать время анимацииы
	//
	void InitAnimationTime(double time);

	//
	// Установить идентификатор текущей анимации
	//
	void SetCurrentAnimationName(std::string);

	//
	// Установить номер текущего кадра
	//
	void SetCurrentFrame(int);

	//
	// Сигнал "кадр изменили через gui"
	//
	void GuiChangedFrameSignal(FaerieFrame frame);

	//
	// Сигнал "кадр изменили через фею"
	//
	void FaerieChangedFrameSignal(FaerieFrame frame);

	//
	// Сигнал начать анимацию
	//
	void StartAnimationSignal(FaerieAnimation* animation);

	//
	// Сигнал закончить анимацию
	//
	void StopAnimationSignal();

	//
	// Сигнал "запущена ли анимация"
	//
	void AnimationIsStopped(bool isStopped);

	//
	// Установить прогресс анимации
	//
	void SetAnimationProgress(float);

public slots:

	//
	// Установить время анимации
	//
	void SetAnimationTime(double time);

	//
	// Сохранить все анимации
	//
	void SaveAll();

	//
	// Отменить все изменения в анимациях
	//
	void DiscardAll();

	//
	// Установить номер текущего кадра ыдля редактирования
	//
	void SetCurrentFrameNumber(int number);

	//
	// Установить текущую анимацию
	//
	void SetCurrentAnimation(const QString& name);

	//
	// Клонировать текущий кадр
	//
	void CloneCurrentFrame();

	//
	// Удалить текущий кадр
	//
	void DeleteCurrentFrame();

	//
	// Кадр изменили через Gui
	//
	void GuiChangedFrame(FaerieFrame frame);

	//
	// Кадр изменили через фею
	//
	void FaerieChangedFrame(FaerieFrame frame);

	//
	// Нажали на кнопку начать анимацию
	//
	void StartAnimationSlot();

	//
	// Нажали на кнопку закончить анимацию
	//
	void StopAnimationSlot();

private:

	FaerieAnimationsCollection* _collection;
		// коллекция анимаций

	FaerieAnimation* _currentAnimation;
		// выбранная анимация

	int _currentFrameNumber;
		// номер текущего кадра

	//
	// Вернуть список анимаций
	//
	QStringList GetAnimationsList();

	//
	// Инициализировать вид текущей анимации
	//
	void InitCurrentAnimationView();

	//
	// Вернуть список кадров
	//
	QStringList GetFramesList();

};
