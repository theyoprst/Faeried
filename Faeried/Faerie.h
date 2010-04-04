#pragma once

#include <QtCore/QObject>

#include "BonesMap.h"

class hgeSprite;
class HGE;
class Bone;

#include "FaerieFrame.h"
#include "FPoint.h"
#include "Point.h"

//
// ���������� ���
//
class Faerie
	: public QObject
{

	Q_OBJECT

public:
	
	//
	// �����������
	//
	explicit Faerie(HGE *hge);

	//
	// ���������
	//
	void Draw(int x, int y);

	//
	// �������� ���
	//
	void Update(float dt);

	//
	// ������� ����� �� �� �����
	//
	Bone* GetBoneByName(std::string boneName);

	//
	// ������� �����
	//
	void OnMouseMove(Point p);

	//
	// �������� �����
	//
	void OnLeftMouseDown(Point p);

	//
	// ��������� ����� ������ ����
	//
	void OnLeftMouseUp(Point p);

private:

	Bone* _rootBone;
		// �������� ����� (��������)

	BonesMap _bonesMap;
		// ����������� "��� - ��������� �� �����"

	Bone* _draggingBone;
		// ��������������� �����

	FPoint _shift;
		// �����

	enum {

		STATE_NOFRAME,
			// ��� �������� �����, ������ �� ������

		STATE_SINGLE_FRAME,
			// ������������ ����������� ���� � ���� ������
		
		STATE_DRAGGING_BONE,
			// ���� ����� ����� �����

	} _state;
		// ������� ���������

public slots:
	
	//
	// ���� "��������� ���� �� ���"
	//
	void GuiChangedFrame(FaerieFrame frame);

	//
	// ����� �� ���������� ���
	//
	void SlotShowFaerie(bool);

signals:

	//
	// ������ "��������� ���� ����� ���"
	//
	void FaerieChangedFrameSignal(FaerieFrame frame);

private:

	//
	// ������� ����� �� �������� ��������� ������
	//
	FaerieFrame CreateFrame();
};
