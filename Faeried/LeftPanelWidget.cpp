#include "LeftPanelWidget.h"

#include <QtGui/QCloseEvent>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QInputDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QMessageBox>
#include <QtGui/QPushButton>

#include "AnimationsComboBox.h"
#include "FaerieAnimationsDelegate.h"
#include "FrameEditorWidget.h"
#include "FramesListWidget.h"
#include "PreviewFaerieWidget.h"

LeftPanelWidget::LeftPanelWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent)
	, _animations(animations)
{
	// всех детей помещаем в вертикальный лэйаут
	QVBoxLayout* verticalLayout = new QVBoxLayout();
	verticalLayout->addLayout(CreateAnimationsLayout());
	verticalLayout->addLayout(CreateTimeLayout());
	verticalLayout->addWidget(CreateFramesWidget(), 0, Qt::AlignLeft);
	verticalLayout->addWidget(CreateFrameSettings(), 0, Qt::AlignLeft);
	verticalLayout->addLayout(CreateButtonsLayout());
	setLayout(verticalLayout);
}

QLayout* LeftPanelWidget::CreateAnimationsLayout() {
	AnimationsComboBox* animationsCombo = new AnimationsComboBox(this);
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), animationsCombo, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(SetAnimationsList(const QStringList&)), animationsCombo, SLOT(SetAnimationsList(const QStringList&)));
	connect(_animations, SIGNAL(SetCurrentAnimationName(std::string)), animationsCombo, SLOT(SetCurrentAnimationName(std::string)));
	connect(animationsCombo, SIGNAL(currentIndexChanged(const QString&)), _animations, SLOT(SetCurrentAnimation(const QString&)));
	animationsCombo->show();

	QPushButton* newAnimationButton = new QPushButton(tr("Новая"));
	newAnimationButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), newAnimationButton, SLOT(setEnabled(bool)));
	connect(newAnimationButton, SIGNAL(clicked()), this, SLOT(AskNewAnimationName()));
	
	QPushButton* deleteAnimationButton = new QPushButton(tr("Удалить"));
	deleteAnimationButton->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
	connect(deleteAnimationButton, SIGNAL(clicked()), this, SLOT(ConfirmDeleteAnimation()));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), deleteAnimationButton, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), deleteAnimationButton, SLOT(setEnabled(bool)));

	QHBoxLayout* line = new QHBoxLayout();
	line->addWidget(animationsCombo);
	line->addWidget(newAnimationButton);
	line->addWidget(deleteAnimationButton);

	return line;
}

QLayout* LeftPanelWidget::CreateTimeLayout() {
	QLabel* labelTime = new QLabel(tr("Продолжительность:"));
	QDoubleSpinBox* spinBox = new QDoubleSpinBox();
	spinBox->setMinimum(0.1);
	spinBox->setMaximum(50.0);
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), spinBox, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), spinBox, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(InitAnimationTime(double)), spinBox, SLOT(setValue(double)));
	connect(spinBox, SIGNAL(valueChanged(double)), _animations, SLOT(SetAnimationTime(double)));

	QHBoxLayout* line = new QHBoxLayout();
	line->addWidget(labelTime);
	line->addWidget(spinBox);
	return line;
}

QWidget* LeftPanelWidget::CreateFramesWidget() {
	FramesListWidget* frames = new FramesListWidget(0);
	connect(frames, SIGNAL(currentRowChanged(int)), _animations, SLOT(SetCurrentFrameNumber(int)));
	connect(_animations, SIGNAL(SetFramesList(const QStringList&)), frames, SLOT(SetFramesList(const QStringList&)));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), frames, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), frames, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(SetCurrentFrame(int)), frames, SLOT(SetCurrentRow(int)));

	// справа выстраиваем кнопочки в столбик
	QPushButton* buttonClone = new QPushButton(tr("Дублировать кадр"));
	buttonClone->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), buttonClone, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), buttonClone, SLOT(setEnabled(bool)));
	connect(buttonClone, SIGNAL(clicked()), _animations, SLOT(CloneCurrentFrame()));

	QPushButton* buttonRemove = new QPushButton(tr("Удалить кадр"));
	buttonRemove->setIcon(style()->standardIcon(QStyle::SP_DialogDiscardButton));
	//connect(_animations, SIGNAL(AnimationIsSelected(bool)), buttonRemove, SLOT(setEnabled(bool)));
	connect(buttonRemove, SIGNAL(clicked()), _animations, SLOT(DeleteCurrentFrame()));
	connect(frames, SIGNAL(MoreThanOneFrame(bool)), buttonRemove, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), buttonRemove, SLOT(setEnabled(bool)));

	QVBoxLayout* column = new QVBoxLayout;
	column->addWidget(buttonClone);
	column->addWidget(buttonRemove);
	column->addStretch(1);

	QHBoxLayout* line = new QHBoxLayout;
	line->addWidget(frames);
	line->addLayout(column);

	QGroupBox* groupBox = new QGroupBox(tr("Кадры анимации"));
	groupBox->setLayout(line);

	return groupBox;
}

QLayout* LeftPanelWidget::CreateButtonsLayout() {
	QPushButton* saveAll = new QPushButton(tr("Сохранить всё"));
	saveAll->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	connect(saveAll, SIGNAL(clicked()), _animations, SLOT(SaveAll()));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), saveAll, SLOT(setEnabled(bool)));

	QPushButton* discardAll = new QPushButton(tr("Отменить всё"));
	discardAll->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
	connect(discardAll, SIGNAL(clicked()), _animations, SLOT(DiscardAll()));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), discardAll, SLOT(setEnabled(bool)));

	QHBoxLayout* line = new QHBoxLayout;
	line->addStretch(1);
	line->addWidget(saveAll);
	line->addWidget(discardAll);
	line->addStretch(1);

	return line;
}

QWidget* LeftPanelWidget::CreateFrameSettings() {
	FrameEditorWidget* frameEditor = new FrameEditorWidget(this);
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), frameEditor, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(AnimationIsStopped(bool)), frameEditor, SLOT(setEnabled(bool)));
	connect(frameEditor, SIGNAL(GuiChangedFrame(FaerieFrame)), _animations, SLOT(GuiChangedFrame(FaerieFrame))); 
	connect(_animations, SIGNAL(FaerieChangedFrameSignal(FaerieFrame)), frameEditor, SLOT(FaerieChandedFrame(FaerieFrame)));
	return frameEditor;
}

void LeftPanelWidget::AskNewAnimationName() {
	bool okPressed = false;
	QString animationName = QInputDialog::getText(this, tr("Имя анимации"), tr("Введите имя анимации"), QLineEdit::Normal, tr(""), &okPressed);
	if (okPressed) {
		QRegExp regExp("[a-zA-Z0-9\\._\\-\\s]+");
		if (regExp.exactMatch(animationName)) {
			if (!_animations->HasAnimation(animationName.toStdString())) {
				_animations->AddAnimation(animationName.toStdString());
			} else {
				QMessageBox animationExists(this);
				animationExists.setText(tr("Анимация с таким именем уже существует"));
				animationExists.setStandardButtons(QMessageBox::Ok);
				animationExists.setIcon(QMessageBox::Warning);
				animationExists.exec();
			}
		} else {
			QMessageBox animationExists(this);
			animationExists.setText(tr("Неправильное имя анимации"));
			animationExists.setDetailedText(tr("Имя должно состоять из латинских букв, цифр и некоторых других знаков"));
			animationExists.setStandardButtons(QMessageBox::Ok);
			animationExists.setIcon(QMessageBox::Warning);
			animationExists.exec();
		}
	}
}

void LeftPanelWidget::ConfirmDeleteAnimation() {
	QMessageBox deleteConfirm(this);
	deleteConfirm.setText(tr("Вы действительно хотите удалить эту анимацию?"));
	deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	deleteConfirm.setDefaultButton(QMessageBox::Yes);
	deleteConfirm.setIcon(QMessageBox::Question);
	int result = deleteConfirm.exec();
	if (result == QMessageBox::Yes) {
		_animations->DeleteCurrentAnimation();
	} else if (result == QMessageBox::No) {
		// ничего не делаем
	} else {
		assert(false);
	}
}