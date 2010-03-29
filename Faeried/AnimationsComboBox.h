#pragma once

#include <QtGui/QComboBox>

//
// ����� ���������� ������ ���� ��������
//
class AnimationsComboBox
	: public QComboBox
{

	Q_OBJECT

public:

	//
	// �����������
	//
	explicit AnimationsComboBox(QWidget* parent);

public slots:

	//
	// ���������� ������ ��������
	//
	void SetAnimationsList(const QStringList& texts);
};