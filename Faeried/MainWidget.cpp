#include "MainWidget.h"

#include <QtCore/QTextCodec>
#include <QtGui/QCloseEvent>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMessageBox>

#include "PlaybackWidget.h"
#include "PreviewFaerieWidget.h"
#include "SettingsWidget.h"

MainWidget::MainWidget()
	: QWidget()
{
	// Ёто дл€ того, чтобы использовать cp1251
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251")); 
	
	PreviewFaerieWidget* preview = new PreviewFaerieWidget(this);
	SettingsWidget* settings = new SettingsWidget(preview);
	settings->setParent(this);
	PlaybackWidget* playback = new PlaybackWidget(this);

	QVBoxLayout* previewAndPlayback = new QVBoxLayout;
	previewAndPlayback->addStretch(1);
	previewAndPlayback->addWidget(preview);
	previewAndPlayback->addWidget(playback);
	previewAndPlayback->addStretch(1);

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(settings);
	layout->addLayout(previewAndPlayback);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
}

void MainWidget::closeEvent(QCloseEvent* event) {
	QMessageBox exitConfirm(this);
	//exitConfirm.setInformativeText(tr("¬ы действительно хотите выйти?"));
	exitConfirm.setText(tr("¬ы действительно хотите выйти?"));
	exitConfirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	exitConfirm.setDefaultButton(QMessageBox::Yes);
	exitConfirm.setIcon(QMessageBox::Question);
	int result = exitConfirm.exec();
	if (result == QMessageBox::Yes) {
		event->accept();
	} else if (result == QMessageBox::No) {
		event->ignore();
	} else {
		assert(false);
	}
}