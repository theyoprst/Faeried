#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;

//
// Класс, содержащий виджеты для управления проигрыванием
//
class PlaybackWidget
	: public QWidget
{

public:

	//
	// Конструктор
	//
	PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

};
