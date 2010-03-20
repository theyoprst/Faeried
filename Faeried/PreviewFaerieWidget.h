#pragma once

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

class HGE;
class Faerie;

//
// ������ ����������� ���;
// �������� ���� hge, ��������� ��������� �� ���� �������� ����� ����� (?)
//
class PreviewFaerieWidget
	: public QWidget
{

	Q_OBJECT

public:
	
	//
	// �����������
	//
	PreviewFaerieWidget(QWidget* parent = 0);

	//
	// �����������
	//
	~PreviewFaerieWidget();

private:

	const static int WIDTH = 800;
		// ������ ����
	
	const static int HEIGHT = 600;
		// ������ ����

	static HGE* _hge;
		// ������ ���� HGE, ����������� ��� ������������� callback-�������

	static Faerie* _faerie;
		// ���

	QTimer _timer;
		// ������

	static QTime _time;
		// ��� �������� � ��������� �������

	//
	// Callback-������� ���������� ����
	//
	static bool FrameFunc();

	//
	// ������ ���
	//
	static void Draw();

	//
	// ��������� ���
	//
	static void Update(float dt);

	//
	// ���������������� HGE
	//
	void InitHGE();


	virtual void paintEvent(QPaintEvent*);


	virtual QPaintEngine * paintEngine () const;

private slots:

	//
	// Callback-������� ���������� ����
	//
	static bool RenderFunc();

};
