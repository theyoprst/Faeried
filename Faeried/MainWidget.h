#pragma once

#include <QtGui/QWidget.h>

//
// ����� �������� ����
//
class MainWidget
	: public QWidget
{

public:

	//
	// ����������� �� ���������
	//
	MainWidget();

private:

	virtual void closeEvent(QCloseEvent* event);
};
