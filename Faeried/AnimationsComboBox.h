#pragma once

#include <QtGui/QComboBox>

//
// Класс выпадающий список имен анимаций
//
class AnimationsComboBox
	: public QComboBox
{

	Q_OBJECT

public:

	//
	// Конструктор
	//
	explicit AnimationsComboBox(QWidget* parent);

public slots:

	//
	// Установить список анимаций
	//
	void SetAnimationsList(const QStringList& texts);
};