#pragma once

#include <QtGui/QItemDelegate>

//
// Делегат спинбокса (для использования в QTableView)
//
class SpinBoxDelegate
	: public QItemDelegate
{

	Q_OBJECT

public:

	//
	// Конструктор - передаем минимальное и максимальное значение спинбокса
	//
	SpinBoxDelegate(int min, int max);

	//
	// Возвращает виджет редактирования при клике на элемент
	// (в данном случае возвращается спинбокс)
	//
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	//
	// Инициализация виджета редактирования
	//
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

	//
	// Запись результата редактирования в модель 
	//
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	//
	// Видимо, установка размеров редакторского виджета :)
	//
	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

	int _min;
		// минимальное значение спинбокса

	int _max;
		// максимальное значение спинбокса
};