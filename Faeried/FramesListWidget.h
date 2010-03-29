#pragma once

#include <QListWidget>

//
// ����� ������� ������ ������
//
class FramesListWidget
	: public QListWidget
{

public:
	
	//
	// �����������
	//
	FramesListWidget(QWidget* parent);

public slots:

	//
	// ���������� ������ ������
	//
	void SetFramesList(const QStringList& framesList); 
};

