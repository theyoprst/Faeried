#pragma once

#include <QListWidget>

//
// Класс виджета списка кадров
//
class FramesListWidget
	: public QListWidget
{

	Q_OBJECT

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

	//
	// Установить номер текущей строки
	//
	void SetCurrentRow(int rowNumber);

	//
	// Обработка сигнала выбранности анимации
	//
	void AnimationIsSelected(bool);

signals:

	//
	// Сигнал того, что установлен более чем один кадр
	//
	void MoreThanOneFrame(bool);

};

