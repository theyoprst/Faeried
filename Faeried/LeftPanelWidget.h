#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;

//
// Виджет настроек феи
//
class LeftPanelWidget
	: public QWidget
{
	
	Q_OBJECT

public:
	
	//
	// Конструктор
	//
	LeftPanelWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

private:

	FaerieAnimationsDelegate* _animations;
		// делегат анимаций
	
	//
	// Создать виджеты управления анимациями
	// и вернуть указатель на них
	//
	QLayout* CreateAnimationsLayout();

	//
	// Создать виджеты управления продолжительностью анимации
	// и вернуть указатель на них
	//
	QLayout* CreateTimeLayout();

	//
	// Создать виджеты управления списком кадров и
	// вернуть указатель на них
	//
	QWidget* CreateFramesWidget();

	//
	// Создать кнопки сохранения / отмены всего
	// и вернуть указатель на них
	//
	QLayout* CreateButtonsLayout();

	//
	// Создать блок настроек кадра
	// и вернуть указатель на него
	//
	QWidget* CreateFrameSettings();

private slots:

	//
	// Спросить имя анимации и создать ее
	//
	void AskNewAnimationName();

	//
	// Подтвердить удаление анимации
	//
	void ConfirmDeleteAnimation();

};
