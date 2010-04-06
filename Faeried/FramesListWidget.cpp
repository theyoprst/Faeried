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

void FramesListWidget::AnimationIsSelected(bool isSelected) {
	if (!isSelected) {
		clear();
		emit MoreThanOneFrame(false);
	}
}
