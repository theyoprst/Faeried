#pragma once

#include <QtGui/QWidget.h>

class FaerieAnimationsDelegate;

//
// ����� �������� ����
//
class MainWidget
	: public QWidget
{

public:

	//
	// �����������
	//
	explicit MainWidget(FaerieAnimationsDelegate* animations);

private:

	//
	// ������� ������
	//
	virtual void closeEvent(QCloseEvent* event);
};
