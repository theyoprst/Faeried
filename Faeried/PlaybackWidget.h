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

	static const int SLIDER_PROGRESS_MAX = 1000;
		// ������������ �������� �������� ���������
		// (����������� ����� ����)

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

	//
	// ������� ��������� ��������
	//
	void SetPlaybackProgressSlot(float);

signals:

	//
	// ���������� ��������
	//
	void StopAnimation();

	//
	// ������ ��������
	//
	void StartAnimation();

	//
	// ���������� �������� �������� ���������
	//
	void SetPlaybackProgress(int);

};
