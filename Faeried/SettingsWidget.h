#pragma once

#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QMainWindow>

class PreviewFaerieWidget;

//
// Виджет настроек феи
//
class SettingsWidget
	: public QWidget
{
public:
	
	//
	// Конструктор
	//
	SettingsWidget(PreviewFaerieWidget* preview);

private:

	PreviewFaerieWidget* _preview;
		// виджет предосмотра

	//
	// Событие закрытия - нужно закрыть окно предосмотра
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
	// Получить блок настроек кадра
	//
	QWidget* CreateFrameSettings();
};
