#pragma once

#include <QtCore/QObject>

#include "BonesMap.h"

class Bone;
class FaerieAnimation;
class hgeSprite;
class HGE;

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

	float _animationTimer;
		// ������ ��������

	FaerieAnimation* _animation;
		// ������� �������� (� ��������� STATE_ANIMATION)

	enum {

		STATE_NOFRAME,
			// ��� �������� �����, ������ �� ������

		STATE_SINGLE_FRAME,
			// ������������ ����������� ���� � ���� ������
		
		STATE_DRAGGING_BONE,
			// ���� ����� ����� �����

		STATE_ANIMATION,
			// ������������� ��������

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

	//
	// ������ �� ������ ������ ��������
	//
	void StartAnimationSlot(FaerieAnimation* animation);

	//
	// ������ �� ������ ��������� ��������
	//
	void StopAnimationSlot();

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
