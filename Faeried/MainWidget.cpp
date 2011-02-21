#include "MainWidget.h"

#include <QtCore/QTextCodec>
#include <QtGui/QCloseEvent>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMessageBox>

#include "LeftPanelWidget.h"
#include "PlaybackWidget.h"
#include "PreviewFaerieWidget.h"

MainWidget::MainWidget(FaerieAnimationsDelegate* animations)
	: QWidget()
{
	// Ёто дл€ того, чтобы использовать cp1251
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251")); 
	
	PreviewFaerieWidget* preview = new PreviewFaerieWidget(this, animations);
	LeftPanelWidget* leftPanel = new LeftPanelWidget(this, animations);
	PlaybackWidget* playback = new PlaybackWidget(this, animations);

	QVBoxLayout* previewAndPlayback = new QVBoxLayout;
	previewAndPlayback->addStretch(1);
	previewAndPlayback->addWidget(preview);
	previewAndPlayback->addWidget(playback);
	previewAndPlayback->addStretch(1);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(leftPanel);
	layout->addLayout(previewAndPlayback);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
}

void MainWidget::closeEvent(QCloseEvent* event) {
	//QMessageBox exitConfirm(this);
	////exitConfirm.setInformativeText(tr("¬ы действительно хотите выйти?"));
	//exitConfirm.setText(tr("¬ы действительно хотите выйти?"));
	//exitConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	//exitConfirm.setDefaultButton(QMessageBox::Yes);
	//exitConfirm.setIcon(QMessageBox::Question);
	//int result = exitConfirm.exec();
	//if (result == QMessageBox::Yes) {
	//	event->accept();
	//} else if (result == QMessageBox::No) {
	//	event->ignore();
	//} else {
	//	assert(false);
	//}
	event->accept();
}