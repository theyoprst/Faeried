#pragma once

#include <QtGui/QWidget.h>

//
// Класс главного окна
//
class MainWidget
	: public QWidget
{

public:

	//
	// Конструктор по умолчанию
	//
	MainWidget();

private:

	virtual void closeEvent(QCloseEvent* event);
};
