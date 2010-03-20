#pragma once

#include <QtGui/QWidget>

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
};
