#pragma once

#include "BonesMap.h"

class hgeSprite;
class HGE;
class Bone;

#include "Point.h"

//
// ���������� ���
//
class Faerie {

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

	enum {
		
		STATE_WAITING,
			// ��������� ��������
		
		STATE_DRAGGING_BONE,
			// ���� ����� ����� �����

	} _state;
		// ������� ����������
};
