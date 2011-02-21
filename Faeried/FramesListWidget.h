#pragma once

#include <QListWidget>

//
// ����� ������� ������ ������
//
class FramesListWidget
	: public QListWidget
{

	Q_OBJECT

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

	//
	// ���������� ����� ������� ������
	//
	void SetCurrentRow(int rowNumber);

	//
	// ��������� ������� ����������� ��������
	//
	void AnimationIsSelected(bool);

signals:

	//
	// ������ ����, ��� ���������� ����� ��� ���� ����
	//
	void MoreThanOneFrame(bool);

};

