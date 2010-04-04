#pragma once

#include <map>
#include <string>

class Bone;

//
// ����� ����������� ����� ����� � ��������� �� ��
//
class BonesMap
	: public std::map<std::string, Bone*>
{

public:

	//
	// �������� �����; ���� ����� ��� ���� ���������, ��������� ������
	//
	void AddBone(std::string boneName, Bone* bone);

	//
	// �������� �����; ���� ����� ����� �� ����, ��������� ������
	//
	Bone* GetBone(std::string boneName);

};
