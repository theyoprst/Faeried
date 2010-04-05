#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;
class QPushButton;

//
// Класс, содержащий виджеты для управления проигрыванием
//
class PlaybackWidget
	: public QWidget
{

	Q_OBJECT

public:

	//
	// Конструктор
	//
	PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

private:

	static const int SLIDER_PROGRESS_MAX = 1000;
		// максимальное значение слайдера прогресса
		// (минимальное равно нулю)

	QPushButton* _playbackButton;
		// кнопка плей (а заодно и пауза)

	enum {
		STATE_STOPPED,
		STATE_PLAYING,
	} _state;
		// текущее состояние

private slots:
	
	//
	// Событие "Кликнули на плей"
	//
	void ClickedPlayButton();

	//
	// Событие изменился прогресс
	//
	void SetPlaybackProgressSlot(float);

signals:

	//
	// Остановить анимацию
	//
	void StopAnimation();

	//
	// Начать анимацию
	//
	void StartAnimation();

	//
	// Установить значение слайдера прогресса
	//
	void SetPlaybackProgress(int);

};
