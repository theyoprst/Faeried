#include "PlaybackWidget.h"

#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

#include "Bone.h"
#include "FaerieAnimationsDelegate.h"

PlaybackWidget::PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent)
	, _state(STATE_STOPPED)
{
	QHBoxLayout* layout = new QHBoxLayout;

	_playbackButton = new QPushButton(this);
	_playbackButton->setToolTip(tr("Запустить/остановить анимацию"));
	_playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	connect(animations, SIGNAL(AnimationIsSelected(bool)), _playbackButton, SLOT(setEnabled(bool)));
	connect(_playbackButton, SIGNAL(clicked()), this, SLOT(ClickedPlayButton()));

	QSlider* playbackSlider = new QSlider(Qt::Horizontal, this);
	playbackSlider->setMinimum(0);
	playbackSlider->setMaximum(SLIDER_PROGRESS_MAX);
	playbackSlider->setEnabled(false);
	connect(this, SIGNAL(SetPlaybackProgress(int)), playbackSlider, SLOT(setValue(int)));

	QComboBox* scalesCombo = new QComboBox(this);
	scalesCombo->setToolTip(tr("Изменить масштаб феи"));
	scalesCombo->addItem(tr("100%"));
	scalesCombo->addItem(tr("200%"));
	scalesCombo->addItem(tr("300%"));
	scalesCombo->addItem(tr("400%"));
	scalesCombo->setCurrentIndex(3);
	connect(scalesCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ScaleChanged(const QString&))); 
	connect(animations, SIGNAL(AnimationIsSelected(bool)), scalesCombo, SLOT(setEnabled(bool)));

	layout->addWidget(_playbackButton);
	layout->addWidget(playbackSlider);
	layout->addWidget(scalesCombo);

	layout->setContentsMargins(0, 0, 5, 5);

	setLayout(layout);

	connect(this, SIGNAL(StartAnimation()), animations, SLOT(StartAnimationSlot()));
	connect(this, SIGNAL(StopAnimation()), animations, SLOT(StopAnimationSlot()));
	connect(animations, SIGNAL(SetAnimationProgress(float)), this, SLOT(SetPlaybackProgressSlot(float)));
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
		emit SetPlaybackProgress(0);
	} else {
		assert(false);
	}
}

void PlaybackWidget::SetPlaybackProgressSlot(float progress) {
	emit SetPlaybackProgress(Math::Round(progress * SLIDER_PROGRESS_MAX));
}

void PlaybackWidget::ScaleChanged(const QString& scale) {
	std::string s = scale.toStdString();
	int percents = Int::Parse(s.substr(0, s.size() - 1).c_str());
	Bone::SetScale(percents / 100.0f);
}