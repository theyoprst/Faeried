#pragma once

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

private:

	Bone* _rootBone;
};
