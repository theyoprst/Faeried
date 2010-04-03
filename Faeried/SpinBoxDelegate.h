#pragma once

#include <QtGui/QItemDelegate>

//
// ������� ��������� (��� ������������� � QTableView)
//
class SpinBoxDelegate
	: public QItemDelegate
{

	Q_OBJECT

public:

	//
	// ����������� - �������� ����������� � ������������ �������� ���������
	//
	SpinBoxDelegate(int min, int max);

	//
	// ���������� ������ �������������� ��� ����� �� �������
	// (� ������ ������ ������������ ��������)
	//
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	//
	// ������������� ������� ��������������
	//
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

	//
	// ������ ���������� �������������� � ������ 
	//
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	//
	// ������, ��������� �������� ������������� ������� :)
	//
	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

	int _min;
		// ����������� �������� ���������

	int _max;
		// ������������ �������� ���������
};