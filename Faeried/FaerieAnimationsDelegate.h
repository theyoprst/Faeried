#pragma once

#include <QtCore/QObject>

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

private:

	FaerieAnimationsCollection* _collection;
		// коллекция анимаций

	FaerieAnimation* _currentAnimation;
		// выбранная анимация

	//
	// Вернуть список анимаций
	//
	QStringList GetAnimationsList();

	//
	// Инициализировать вид текущей анимации
	//
	void InitCurrentAnimationView();
};
