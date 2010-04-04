#pragma once

#include <QtGui/QWidget>

class FaerieAnimationsDelegate;
class QPushButton;

//
// �����, ���������� ������� ��� ���������� �������������
//
class PlaybackWidget
	: public QWidget
{

	Q_OBJECT

public:

	//
	// �����������
	//
	PlaybackWidget(QWidget* parent, FaerieAnimationsDelegate* animations);

private:

	QPushButton* _playbackButton;
		// ������ ���� (� ������ � �����)

	enum {
		STATE_STOPPED,
		STATE_PLAYING,
	} _state;
		// ������� ���������

private slots:
	
	//
	// ������� "�������� �� ����"
	//
	void ClickedPlayButton();

signals:

	//
	// ���������� ��������
	//
	void StopAnimation();

	//
	// ������ ��������
	//
	void StartAnimation();

};
