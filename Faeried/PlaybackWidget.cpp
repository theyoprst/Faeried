#include "PlaybackWidget.h"

#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

PlaybackWidget::PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout;

	QPushButton* playbackButton = new QPushButton(this);
	playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

	QSlider* playbackSlider = new QSlider(Qt::Horizontal, this);
	playbackSlider->setMinimum(0);
	playbackSlider->setMaximum(1000);
	playbackSlider->setEnabled(false);

	QComboBox* scalesCombo = new QComboBox(this);
	scalesCombo->addItem(tr("100%"));
	scalesCombo->addItem(tr("200%"));
	scalesCombo->addItem(tr("300%"));
	scalesCombo->addItem(tr("400%"));

	layout->addWidget(playbackButton);
	layout->addWidget(playbackSlider);
	layout->addWidget(scalesCombo);

	layout->setContentsMargins(0, 0, 5, 5);

	setLayout(layout);
}