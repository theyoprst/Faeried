#pragma once

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

class Bone;
class Faerie;
class HGE;

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

	//
	// ������� ����� �� �����
	//
	Bone* GetBoneByName(std::string boneName);

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

	/// TODO: � ������ �� ��� �����?
	virtual void paintEvent(QPaintEvent*);
	virtual QPaintEngine * paintEngine () const;

private slots:

	//
	// Callback-������� ���������� ����
	//
	static bool RenderFunc();

};
