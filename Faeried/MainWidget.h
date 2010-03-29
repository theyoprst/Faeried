#pragma once

#include <QtGui/QWidget.h>

class FaerieAnimationsDelegate;

//
// Класс главного окна
//
class MainWidget
	: public QWidget
{

public:

	//
	// Конструктор
	//
	explicit MainWidget(FaerieAnimationsDelegate* animations);

private:

	//
	// Событие выхода
	//
	virtual void closeEvent(QCloseEvent* event);
};
