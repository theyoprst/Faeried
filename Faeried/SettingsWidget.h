#pragma once

#include <QtGui/QWidget>

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
};
