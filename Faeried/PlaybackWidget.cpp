#include "PlaybackWidget.h"

#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

#include "FaerieAnimationsDelegate.h"

PlaybackWidget::PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent)
	, _state(STATE_STOPPED)
{
	QHBoxLayout* layout = new QHBoxLayout;

	_playbackButton = new QPushButton(this);
	_playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	connect(animations, SIGNAL(AnimationIsSelected(bool)), _playbackButton, SLOT(setEnabled(bool)));
	connect(_playbackButton, SIGNAL(clicked()), this, SLOT(ClickedPlayButton()));

	QSlider* playbackSlider = new QSlider(Qt::Horizontal, this);
	playbackSlider->setMinimum(0);
	playbackSlider->setMaximum(1000);
	playbackSlider->setEnabled(false);

	QComboBox* scalesCombo = new QComboBox(this);
	scalesCombo->addItem(tr("100%"));
	scalesCombo->addItem(tr("200%"));
	scalesCombo->addItem(tr("300%"));
	scalesCombo->addItem(tr("400%"));

	layout->addWidget(_playbackButton);
	layout->addWidget(playbackSlider);
	layout->addWidget(scalesCombo);

	layout->setContentsMargins(0, 0, 5, 5);

	setLayout(layout);

	connect(this, SIGNAL(StartAnimation()), animations, SLOT(StartAnimationSlot()));
	connect(this, SIGNAL(StopAnimation()), animations, SLOT(StopAnimationSlot()));
}

void PlaybackWidget::ClickedPlayButton() {
	if (_state == STATE_STOPPED) {
		_state = STATE_PLAYING;
		_playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
		emit StartAnimation();
	} else if (_state == STATE_PLAYING) {
		_state = STATE_STOPPED;
		_playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		emit StopAnimation();
	} else {
		assert(false);
	}
}