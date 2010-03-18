#include <QtGui/QApplication>

#include "PreviewFaerieWidget.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	PreviewFaerieWidget window;
	window.show();
	return app.exec();
}