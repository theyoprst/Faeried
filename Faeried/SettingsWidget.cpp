#include "SettingsWidget.h"

#include <QtGui/QCloseEvent>
#include "PreviewFaerieWidget.h"

SettingsWidget::SettingsWidget(PreviewFaerieWidget* preview)
	: QWidget()
	, _preview(preview)
{
}

void SettingsWidget::closeEvent(QCloseEvent* event) {
	_preview->close();
	event->accept();
}
