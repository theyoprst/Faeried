#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;

//
// �����, ���������� ������� ��� ���������� �������������
//
class PlaybackWidget
	: public QWidget
{

public:

	//
	// �����������
	//
	PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

};
