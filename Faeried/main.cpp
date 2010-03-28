#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

#include "MainWidget.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWidget mainWidget;
	mainWidget.show();
	return app.exec();
}