#include "SettingsWidget.h"

#include <QtGui/QCloseEvent>
#include <QtGui/QGridLayout>

#include "AngleSliderWidget.h"
#include "PreviewFaerieWidget.h"

SettingsWidget::SettingsWidget(PreviewFaerieWidget* preview)
	: QWidget()
	, _preview(preview)
{
	QSlider* sliderHead = new AngleSliderWidget(preview->GetBoneByName("head"));
	QSlider* sliderBody = new AngleSliderWidget(preview->GetBoneByName("body"));
	QSlider* sliderLeftArm = new AngleSliderWidget(preview->GetBoneByName("leftArm"));
	QSlider* sliderRightArm = new AngleSliderWidget(preview->GetBoneByName("rightArm"));
	QSlider* sliderLeftForearm = new AngleSliderWidget(preview->GetBoneByName("leftForearm"));
	QSlider* sliderRightForearm = new AngleSliderWidget(preview->GetBoneByName("rightForearm"));
	QSlider* sliderPelvis = new AngleSliderWidget(preview->GetBoneByName("pelvis"));
	QSlider* sliderLeftThigh = new AngleSliderWidget(preview->GetBoneByName("leftThigh"));
	QSlider* sliderLeftLeg = new AngleSliderWidget(preview->GetBoneByName("leftLeg"));
	QSlider* sliderRightThigh = new AngleSliderWidget(preview->GetBoneByName("rightThigh"));
	QSlider* sliderRightLeg = new AngleSliderWidget(preview->GetBoneByName("rightLeg"));

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(sliderHead, 0, 1);
	grid->addWidget(sliderLeftArm, 1, 0);
	grid->addWidget(sliderBody, 1, 1);
	grid->addWidget(sliderRightArm, 1, 2);
	grid->addWidget(sliderLeftForearm, 2, 0);
	grid->addWidget(sliderRightForearm, 2, 2);
	grid->addWidget(sliderPelvis, 3, 1);
	grid->addWidget(sliderLeftThigh, 4, 0);
	grid->addWidget(sliderRightThigh, 4, 2);
	grid->addWidget(sliderLeftLeg, 5, 0);
	grid->addWidget(sliderRightLeg, 5, 2);

	setLayout(grid);
}

void SettingsWidget::closeEvent(QCloseEvent* event) {
	_preview->close();
	event->accept();
}

void SettingsWidget::focusInEvent(QFocusEvent * event) {
	_preview->show();
	event->accept();
}