#include "FramesListWidget.h"

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