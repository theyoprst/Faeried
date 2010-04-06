#include "FramesListWidget.h"

#include <QtCore/QEvent>

FramesListWidget::FramesListWidget(QWidget* parent)
	: QListWidget(parent)
{
}

void FramesListWidget::SetFramesList(const QStringList& framesList) {
	clear();
	addItems(framesList);
	emit MoreThanOneFrame(framesList.size() > 1);
}

void FramesListWidget::SetCurrentRow(int rowNumber) {
	setCurrentRow(rowNumber);
}

void FramesListWidget::changeEvent(QEvent* event) {
	if (event->type() == QEvent::EnabledChange) {
		if (!isEnabled()) {
			clear();
			emit MoreThanOneFrame(false);
		}
	}
}