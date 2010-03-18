#pragma once

#include <QtGui/QWidget>

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

private:

	const static int WIDTH = 800;
		// ������ ����
	
	const static int HEIGHT = 600;
		// ������ ����

	static HGE* _hge;
		// ������ ���� HGE, ����������� ��� ������������� callback-�������

	//
	// Callback-������� ���������� ����
	//
	static bool FrameFunc();

	//
	// Callback-������� ���������� ����
	//
	static bool RenderFunc();

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
};
