#pragma once

#include <QtGui/QItemDelegate>

//
// Делегат, который запрещает редактирование (для использования в QTableView)
//
class NoEditDelegate
	: public QItemDelegate
{
	
	Q_OBJECT

public:

	//
	// Конструктор
	//
	NoEditDelegate();

	//
	// Создать редактор для редактирования - 
	// не создаем ничего и возвращаем NULL
	//
	QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};