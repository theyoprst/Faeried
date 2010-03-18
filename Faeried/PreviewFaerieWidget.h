#pragma once

#include <QtGui/QWidget>

class HGE;

class PreviewFaerieWidget
	: public QWidget
{

public:
	
	//
	// Конструктор
	//
	PreviewFaerieWidget(QWidget* parent = 0);

	//
	// Декструктор
	//
	~PreviewFaerieWidget();

private:

	const static int WIDTH = 800;
		// ширина окна
	
	const static int HEIGHT = 600;
		// высота окна

	static HGE* _hge;
		// объект окна HGE, статический для использования callback-функций

	//
	// Callback-функция обновления окна
	//
	static bool FrameFunc();

	//
	// Callback-функция прорисовки окна
	//
	static bool RenderFunc();

	//
	// Рисуем фею
	//
	static void Draw();

	//
	// Обновляем фею
	//
	static void Update(float dt);

	//
	// Инициализировать HGE
	//
	void InitHGE();
};
