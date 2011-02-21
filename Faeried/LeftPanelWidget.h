#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;

//
// ������ �������� ���
//
class LeftPanelWidget
	: public QWidget
{
	
	Q_OBJECT

public:
	
	//
	// �����������
	//
	LeftPanelWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

private:

	FaerieAnimationsDelegate* _animations;
		// ������� ��������
	
	//
	// ������� ������� ���������� ����������
	// � ������� ��������� �� ���
	//
	QLayout* CreateAnimationsLayout();

	//
	// ������� ������� ���������� ������������������ ��������
	// � ������� ��������� �� ���
	//
	QLayout* CreateTimeLayout();

	//
	// ������� ������� ���������� ������� ������ �
	// ������� ��������� �� ���
	//
	QWidget* CreateFramesWidget();

	//
	// ������� ������ ���������� / ������ �����
	// � ������� ��������� �� ���
	//
	QLayout* CreateButtonsLayout();

	//
	// ������� ���� �������� �����
	// � ������� ��������� �� ����
	//
	QWidget* CreateFrameSettings();

private slots:

	//
	// �������� ��� �������� � ������� ��
	//
	void AskNewAnimationName();

	//
	// ����������� �������� ��������
	//
	void ConfirmDeleteAnimation();

};
