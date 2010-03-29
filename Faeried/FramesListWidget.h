#pragma once

#include <QListWidget>

//
// Класс виджета списка кадров
//
class FramesListWidget
	: public QListWidget
{

public:
	
	//
	// Конструктор
	//
	FramesListWidget(QWidget* parent);

public slots:

	//
	// Установить список кадров
	//
	void SetFramesList(const QStringList& framesList); 
};

