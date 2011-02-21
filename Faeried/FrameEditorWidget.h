#pragma once

#include <QtGui/QTableView>
#include "FaerieFrame.h"

class QStandardItemModel;

//
// Виджет редактирования одного кадра анимации
//
class FrameEditorWidget
	: public QTableView
{

	Q_OBJECT

public:
	
	//
	// Конструктор
	//
	FrameEditorWidget(QWidget* parent);

signals:
	
	//
	// Сигнал, посылаемый как только изменили кадр
	//
	void GuiChangedFrame(FaerieFrame frame);

private:

	bool _isInit;
		// находимся ли в инициализации
		// (нужно чтобы не посылать сообщения об изменениях)

	QStandardItemModel* _model;

	//
	// Создаем кадр на основе введенных данных
	//
	FaerieFrame CreateFrame();

private slots:

	//
	// Обработка сигнала "изменилась таблица"
	//
	void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);

	//
	// Обработка сигнала "фея изменила кадр"
	//
	void FaerieChandedFrame(FaerieFrame frame);

};
