#pragma once

#include "BonesMap.h"

class hgeSprite;
class HGE;
class Bone;

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
	void Draw();

	//
	// �������� ���
	//
	void Update(float dt);

	//
	// ������� ����� �� �� �����
	//
	Bone* GetBoneByName(std::string boneName);

private:

	Bone* _rootBone;

	BonesMap _bonesMap;
		// ����������� "��� - ��������� �� �����"
};
