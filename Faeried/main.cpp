#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

#include "PreviewFaerieWidget.h"
#include "SettingsWidget.h"

int main(int argc, char* argv[]) {

	QApplication app(argc, argv);
	
	PreviewFaerieWidget preview;
	preview.show();

	SettingsWidget settings(&preview);
	settings.show();

	//QObject::connect(&app, SIGNAL(aboutToQuit()), preview, SLOT(OnQuit()));
	QObject::connect(&settings, SIGNAL(exit()), &app, SLOT(quit()));
	
	return app.exec();
}