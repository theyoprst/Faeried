#pragma once

#include <QtGui/QTableView>
#include "FaerieFrame.h"

class QStandardItemModel;

//
// ������ �������������� ������ ����� ��������
//
class FrameEditorWidget
	: public QTableView
{

	Q_OBJECT

public:
	
	//
	// �����������
	//
	FrameEditorWidget(QWidget* parent);

signals:
	
	//
	// ������, ���������� ��� ������ �������� ����
	//
	void GuiChangedFrame(FaerieFrame frame);

private:

	bool _isInit;
		// ��������� �� � �������������
		// (����� ����� �� �������� ��������� �� ����������)

	QStandardItemModel* _model;

	//
	// ������� ���� �� ������ ��������� ������
	//
	FaerieFrame CreateFrame();

private slots:

	//
	// ��������� ������� "���������� �������"
	//
	void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);

	//
	// ��������� ������� "��� �������� ����"
	//
	void FaerieChandedFrame(FaerieFrame frame);

};
