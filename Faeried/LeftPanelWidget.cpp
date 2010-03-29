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
#include "FramesListWidget.h"
#include "PreviewFaerieWidget.h"

LeftPanelWidget::LeftPanelWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent)
	, _animations(animations)
{
	// ���� ����� �������� � ������������ ������
	QVBoxLayout* verticalLayout = new QVBoxLayout();
	verticalLayout->addLayout(CreateAnimationsLayout());
	verticalLayout->addLayout(CreateTimeLayout());
	verticalLayout->addLayout(CreateFramesListLayout());
	verticalLayout->addWidget(CreateFrameSettings(), 0, Qt::AlignLeft);
	verticalLayout->addLayout(CreateButtonsLayout());
	setLayout(verticalLayout);
}

QLayout* LeftPanelWidget::CreateAnimationsLayout() {
	AnimationsComboBox* animationsCombo = new AnimationsComboBox(this);
	connect(_animations, SIGNAL(SetAnimationsList(const QStringList&)), animationsCombo, SLOT(SetAnimationsList(const QStringList&)));
	connect(_animations, SIGNAL(SetCurrentAnimation(std::string)), animationsCombo, SLOT(SetCurrentAnimation(std::string)));
	animationsCombo->show();

	QPushButton* newAnimationButton = new QPushButton(tr("�����"));
	newAnimationButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
	connect(newAnimationButton, SIGNAL(clicked()), this, SLOT(AskNewAnimationName()));
	
	QPushButton* deleteAnimationButton = new QPushButton(tr("�������"));
	deleteAnimationButton->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));
	connect(deleteAnimationButton, SIGNAL(clicked()), this, SLOT(ConfirmDeleteAnimation()));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), deleteAnimationButton, SLOT(setEnabled(bool)));

	QHBoxLayout* line = new QHBoxLayout();
	line->addWidget(animationsCombo);
	line->addWidget(newAnimationButton);
	line->addWidget(deleteAnimationButton);

	return line;
}

QLayout* LeftPanelWidget::CreateTimeLayout() {
	QLabel* labelTime = new QLabel(tr("�����������������:"));
	QDoubleSpinBox* spinBox = new QDoubleSpinBox();
	spinBox->setMinimum(0.1);
	spinBox->setMaximum(50.0);
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), spinBox, SLOT(setEnabled(bool)));
	connect(_animations, SIGNAL(InitAnimationTime(float)), spinBox, SLOT(setValue(double)));
	connect(spinBox, SIGNAL(valueChanged(double)), _animations, SLOT(SetAnimationTime(float)));

	QHBoxLayout* line = new QHBoxLayout();
	line->addWidget(labelTime);
	line->addWidget(spinBox);
	return line;
}

QLayout* LeftPanelWidget::CreateFramesListLayout() {
	FramesListWidget* frames = new FramesListWidget(0);
	connect(frames, SIGNAL(currentRowChanged(int)), _animations, SLOT(SetCurrentFrameNumber(int)));
	connect(_animations, SIGNAL(SetFramesList(const QStringList&)), frames, SLOT(SetFramesList(const QStringList&)));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), frames, SLOT(setEnabled(bool)));

	// ������ ����������� �������� � �������
	QPushButton* buttonClone = new QPushButton(tr("�����������"));
	buttonClone->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), buttonClone, SLOT(setEnabled(bool)));

	QPushButton* buttonRemove = new QPushButton(tr("�������"));
	buttonRemove->setIcon(style()->standardIcon(QStyle::SP_DialogDiscardButton));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), buttonRemove, SLOT(setEnabled(bool)));

	QVBoxLayout* column = new QVBoxLayout;
	column->addWidget(buttonClone);
	column->addWidget(buttonRemove);
	column->addStretch(1);

	QHBoxLayout* line = new QHBoxLayout;
	line->addWidget(frames);
	line->addLayout(column);
	return line;
}

QLayout* LeftPanelWidget::CreateButtonsLayout() {
	QPushButton* saveAll = new QPushButton(tr("��������� ��"));
	saveAll->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	connect(saveAll, SIGNAL(clicked()), _animations, SLOT(SaveAll()));

	QPushButton* discardAll = new QPushButton(tr("�������� ��"));
	discardAll->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
	connect(discardAll, SIGNAL(clicked()), _animations, SLOT(DiscardAll()));

	QHBoxLayout* line = new QHBoxLayout;
	line->addStretch(1);
	line->addWidget(saveAll);
	line->addWidget(discardAll);
	line->addStretch(1);

	connect(_animations, SIGNAL(AnimationIsSelected(bool)), line, SLOT(setEnabled(bool)));

	return line;
}

QWidget* LeftPanelWidget::CreateFrameSettings() {
	QGroupBox* groupBox = new QGroupBox(tr("��������� �����"));
	QGridLayout* grid = new QGridLayout;
	grid->addWidget(new QLabel(tr("���� ��������")), 0, 0);
	grid->addWidget(new QLabel(tr("���� ��������")), 1, 0);
	grid->addWidget(new QLabel(tr("���� ������")), 2, 0);
	grid->addWidget(new QLabel(tr("���� ������ ����������")), 3, 0);
	grid->addWidget(new QLabel(tr("���� ����� ����")), 4, 0);
	grid->addWidget(new QLabel(tr("���� ������� ����������")), 5, 0);
	grid->addWidget(new QLabel(tr("���� ������ ����")), 6, 0);
	grid->addWidget(new QLabel(tr("���� ������ �����")), 7, 0);
	grid->addWidget(new QLabel(tr("���� ����� ������")), 8, 0);
	grid->addWidget(new QLabel(tr("���� ������� �����")), 9, 0);
	grid->addWidget(new QLabel(tr("���� ������ ������")), 10, 0);
	grid->addWidget(new QLabel(tr("�������� �� x")), 11, 0);
	grid->addWidget(new QLabel(tr("�������� �� y")), 12, 0);
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
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), groupBox, SLOT(setEnabled(bool)));
	grid->setVerticalSpacing(1);
	return groupBox;
}

void LeftPanelWidget::AskNewAnimationName() {
	bool okPressed = false;
	QString animationName = QInputDialog::getText(this, tr("��� ��������"), tr("������� ��� ��������"), QLineEdit::Normal, tr(""), &okPressed);
	if (okPressed) {
		QRegExp regExp("[a-zA-Z0-9\\._\\-\\s]+");
		if (regExp.exactMatch(animationName)) {
			if (!_animations->HasAnimation(animationName.toStdString())) {
				_animations->AddAnimation(animationName.toStdString());
			} else {
				QMessageBox animationExists(this);
				animationExists.setText(tr("�������� � ����� ������ ��� ����������"));
				animationExists.setStandardButtons(QMessageBox::Ok);
				animationExists.setIcon(QMessageBox::Warning);
				animationExists.exec();
			}
		} else {
			QMessageBox animationExists(this);
			animationExists.setText(tr("������������ ��� ��������"));
			animationExists.setDetailedText(tr("��� ������ �������� �� ��������� ����, ���� � ��������� ������ ������"));
			animationExists.setStandardButtons(QMessageBox::Ok);
			animationExists.setIcon(QMessageBox::Warning);
			animationExists.exec();
		}
	}
}

void LeftPanelWidget::ConfirmDeleteAnimation() {
	QMessageBox deleteConfirm(this);
	deleteConfirm.setText(tr("�� ������������� ������ ������� ��� ��������?"));
	deleteConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	deleteConfirm.setDefaultButton(QMessageBox::Yes);
	deleteConfirm.setIcon(QMessageBox::Question);
	int result = deleteConfirm.exec();
	if (result == QMessageBox::Yes) {
		_animations->DeleteCurrentAnimation();
	} else if (result == QMessageBox::No) {
		// ������ �� ������
	} else {
		assert(false);
	}
}