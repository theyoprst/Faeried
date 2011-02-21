#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

#include "FaerieAnimationsCollection.h"
#include "FaerieAnimationsDelegate.h"
#include "MainWidget.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	FaerieAnimationsCollection animations("animations.xml");
	FaerieAnimationsDelegate animationsDelegate(&animations);
	MainWidget mainWidget(&animationsDelegate);
	animationsDelegate.InitView();
	mainWidget.show();
	
	// Перемещаем окно примерно по центру экрана (при моем разрешении :)
	mainWidget.move(75, 150);
	
	return app.exec();
}