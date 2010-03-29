#include "FramesListWidget.h"

FramesListWidget::FramesListWidget(QWidget* parent)
	: QListWidget(parent)
{
}

void FramesListWidget::SetFramesList(const QStringList& framesList) {
	clear();
	addItems(framesList);
}
