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
	return app.exec();
}