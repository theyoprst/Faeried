#pragma once

#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>

class PreviewFaerieWidget;

//
// ������ �������� ���
//
class SettingsWidget
	: public QWidget
{
public:
	
	//
	// �����������
	//
	SettingsWidget(PreviewFaerieWidget* preview);

private:

	PreviewFaerieWidget* _preview;
		// ������ �����������

	//
	// ������� �������� - ����� ������� ���� �����������
	//
	virtual void closeEvent(QCloseEvent* event);

	virtual void focusInEvent(QFocusEvent * event);

	QLayout* GetLine0();
	QLayout* GetLine1();
	QLayout* GetLine2();
	QLayout* GetLine3();
	QLayout* GetLine4();
	QLayout* GetLine5();

	//
	// �������� ���� �������� �����
	//
	QWidget* CreateFrameSettings();
};
