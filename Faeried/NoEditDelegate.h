#pragma once

#include <QtGui/QItemDelegate>

//
// �������, ������� ��������� �������������� (��� ������������� � QTableView)
//
class NoEditDelegate
	: public QItemDelegate
{
	
	Q_OBJECT

public:

	//
	// �����������
	//
	NoEditDelegate();

	//
	// ������� �������� ��� �������������� - 
	// �� ������� ������ � ���������� NULL
	//
	QWidget *createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;

};