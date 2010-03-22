#pragma once

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

#include "Point.h"

class Bone;
class Faerie;
class HGE;

//
// Виджет предосмотра феи;
// содержит окно hge, принимает сообщения от окна настроек через слоты (?)
//
class PreviewFaerieWidget
	: public QWidget
{

	Q_OBJECT

public:
	
	//
	// Конструктор
	//
	PreviewFaerieWidget(QWidget* parent = 0);

	//
	// Декструктор
	//
	~PreviewFaerieWidget();

	//
	// Вернуть кость по имени
	//
	Bone* GetBoneByName(std::string boneName);

private:

	const static int WIDTH = 800;
		// ширина окна
	
	const static int HEIGHT = 600;
		// высота окна

	static HGE* _hge;
		// объект окна HGE, статический для использования callback-функций

	static Faerie* _faerie;
		// фея

	QTimer _timer;
		// таймер

	static QTime _time;
		// для привязки к реальному времени

	//
	// Callback-функция обновления окна
	//
	static bool FrameFunc();

	//
	// Рисуем фею
	//
	static void Draw();

	//
	// Обновляем фею
	//
	static void Update(float dt);

	//
	// Обработать сообщения от Hge
	//
	static void ProcessHgeMessages();

	//
	// Инициализировать HGE
	//
	void InitHGE();

private slots:

	//
	// Callback-функция прорисовки окна
	//
	static bool RenderFunc();

};
