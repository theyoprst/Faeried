#include "SettingsWidget.h"

#include <QtGui/QCloseEvent>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

#include "AngleSliderWidget.h"
#include "PreviewFaerieWidget.h"

SettingsWidget::SettingsWidget(PreviewFaerieWidget* preview)
	: QWidget()
	, _preview(preview)
{
	// всех детей помещаем в вертикальный лэйаут
	QVBoxLayout* verticalLayout = new QVBoxLayout();
	verticalLayout->addLayout(GetLine0());
	verticalLayout->addLayout(GetLine1());
	verticalLayout->addLayout(GetLine2());
	verticalLayout->addLayout(GetLine3());
	verticalLayout->addWidget(CreateFrameSettings(), 0, Qt::AlignLeft);
	verticalLayout->addLayout(GetLine4());
	setLayout(verticalLayout);

	//setDockNestingEnabled();
	//this->setDockOptions(QMainWindow::DockOption::AllowNestedDocks);
	//QSlider* sliderHead = new AngleSliderWidget(preview->GetBoneByName("head"));
	//QSlider* sliderBody = new AngleSliderWidget(preview->GetBoneByName("body"));
	//QSlider* sliderLeftArm = new AngleSliderWidget(preview->GetBoneByName("leftArm"));
	//QSlider* sliderRightArm = new AngleSliderWidget(preview->GetBoneByName("rightArm"));
	//QSlider* sliderLeftForearm = new AngleSliderWidget(preview->GetBoneByName("leftForearm"));
	//QSlider* sliderRightForearm = new AngleSliderWidget(preview->GetBoneByName("rightForearm"));
	//QSlider* sliderPelvis = new AngleSliderWidget(preview->GetBoneByName("pelvis"));
	//QSlider* sliderLeftThigh = new AngleSliderWidget(preview->GetBoneByName("leftThigh"));
	//QSlider* sliderLeftLeg = new AngleSliderWidget(preview->GetBoneByName("leftLeg"));
	//QSlider* sliderRightThigh = new AngleSliderWidget(preview->GetBoneByName("rightThigh"));
	//QSlider* sliderRightLeg = new AngleSliderWidget(preview->GetBoneByName("rightLeg"));

	//QGridLayout* grid = new QGridLayout();
	//grid->addWidget(sliderHead, 0, 1);
	//grid->addWidget(sliderLeftArm, 1, 0);
	//grid->addWidget(sliderBody, 1, 1);
	//grid->addWidget(sliderRightArm, 1, 2);
	//grid->addWidget(sliderLeftForearm, 2, 0);
	//grid->addWidget(sliderRightForearm, 2, 2);
	//grid->addWidget(sliderPelvis, 3, 1);
	//grid->addWidget(sliderLeftThigh, 4, 0);
	//grid->addWidget(sliderRightThigh, 4, 2);
	//grid->addWidget(sliderLeftLeg, 5, 0);
	//grid->addWidget(sliderRightLeg, 5, 2);

	//setLayout(grid);

}

QLayout* SettingsWidget::GetLine0() {
	QLabel* label = new QLabel(tr("Выберите анимацию:"), this);
	QVBoxLayout* line0 = new QVBoxLayout;
	line0->addWidget(label);
	return line0;
}

QLayout* SettingsWidget::GetLine1() {
	QComboBox* animationsCombo = new QComboBox(this);
	animationsCombo->addItem(tr("animation1"));
	animationsCombo->addItem(tr("animation2"));
	animationsCombo->show();

	//QPushButton* playButton = new QPushButton();
	//playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

	QPushButton* newAnimationButton = new QPushButton(tr("Создать"));
	newAnimationButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
	
	QPushButton* deleteAnimationButton = new QPushButton(tr("Удалить"));
	deleteAnimationButton->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));

	QHBoxLayout* line1 = new QHBoxLayout();
	line1->addWidget(animationsCombo, 0, Qt::AlignLeft | Qt::AlignTop);
	//line1->addWidget(playButton, 0, Qt::AlignLeft | Qt::AlignTop);
	line1->addWidget(newAnimationButton);
	line1->addWidget(deleteAnimationButton);

	return line1;

}

QLayout* SettingsWidget::GetLine2() {
	QLabel* labelTime = new QLabel(tr("Продолжительность:"));
	QDoubleSpinBox* spinBox = new QDoubleSpinBox();
	spinBox->setMinimum(0.1);
	spinBox->setMaximum(50.0);
	QHBoxLayout* line2 = new QHBoxLayout();
	line2->addWidget(labelTime);
	line2->addWidget(spinBox);
	return line2;
}

QLayout* SettingsWidget::GetLine3() {
	QListWidget* frames = new QListWidget();
	new QListWidgetItem(tr("Frame#1"), frames);
	new QListWidgetItem(tr("Frame#2"), frames);

	// справа выстраиваем кнопочки в столбик
	QPushButton* buttonClone = new QPushButton(tr("Дублировать"));
	buttonClone->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

	QPushButton* buttonRemove = new QPushButton(tr("Удалить"));
	buttonRemove->setIcon(style()->standardIcon(QStyle::SP_DialogDiscardButton));

	QVBoxLayout* column = new QVBoxLayout;
	column->addWidget(buttonClone);
	column->addWidget(buttonRemove);
	column->addStretch(1);

	QHBoxLayout* line = new QHBoxLayout;
	line->addWidget(frames);
	line->addLayout(column);
	return line;
}

QLayout* SettingsWidget::GetLine4() {
	QPushButton* saveAll = new QPushButton(tr("Сохранить всё"));
	saveAll->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));

	QPushButton* discardAll = new QPushButton(tr("Отменить всё"));
	discardAll->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
	QHBoxLayout* line = new QHBoxLayout;
	line->addStretch(1);
	line->addWidget(saveAll);
	line->addWidget(discardAll);
	line->addStretch(1);
	return line;
}

QWidget* SettingsWidget::CreateFrameSettings() {
	QGroupBox* groupBox = new QGroupBox(tr("Настройки кадра"));
	QGridLayout* grid = new QGridLayout;
	grid->addWidget(new QLabel(tr("Угол поясницы")), 0, 0);
	grid->addWidget(new QLabel(tr("Угол туловища")), 1, 0);
	grid->addWidget(new QLabel(tr("Угол головы")), 2, 0);
	grid->addWidget(new QLabel(tr("Угол левого предплечья")), 3, 0);
	grid->addWidget(new QLabel(tr("Угол левой руки")), 4, 0);
	grid->addWidget(new QLabel(tr("Угол правого предплечья")), 5, 0);
	grid->addWidget(new QLabel(tr("Угол правой руки")), 6, 0);
	grid->addWidget(new QLabel(tr("Угол левого бедра")), 7, 0);
	grid->addWidget(new QLabel(tr("Угол левой голени")), 8, 0);
	grid->addWidget(new QLabel(tr("Угол правого бедра")), 9, 0);
	grid->addWidget(new QLabel(tr("Угол правой голени")), 10, 0);
	grid->addWidget(new QLabel(tr("Смещение по x")), 11, 0);
	grid->addWidget(new QLabel(tr("Смещение по y")), 12, 0);
	grid->addWidget(new QSpinBox, 0, 1);
	grid->addWidget(new QSpinBox, 1, 1);
	grid->addWidget(new QSpinBox, 2, 1);
	grid->addWidget(new QSpinBox, 3, 1);
	grid->addWidget(new QSpinBox, 4, 1);
	grid->addWidget(new QSpinBox, 5, 1);
	grid->addWidget(new QSpinBox, 6, 1);
	grid->addWidget(new QSpinBox, 7, 1);
	grid->addWidget(new QSpinBox, 8, 1);
	grid->addWidget(new QSpinBox, 9, 1);
	grid->addWidget(new QSpinBox, 10, 1);
	grid->addWidget(new QSpinBox, 11, 1);
	grid->addWidget(new QSpinBox, 12, 1);
	groupBox->setLayout(grid);
	grid->setVerticalSpacing(1);
	//grid->setContentsMargins(0, 0, 0, 0);
	return groupBox;
}

void SettingsWidget::closeEvent(QCloseEvent* event) {
	//_preview->close();
	event->accept();
}

void SettingsWidget::focusInEvent(QFocusEvent * event) {
	//_preview->activateWindow();
	//this->activateWindow();
	//_preview->repaint();
	//_preview->update();
	//_preview->focusWidget();
	//_preview->showNormal();
	event->accept();
}
