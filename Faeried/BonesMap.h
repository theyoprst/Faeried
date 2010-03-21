#pragma once

#include <map>
#include <string>

class Bone;

//
// ����� ����������� ����� ����� � ��������� �� ��
//
class BonesMap
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

private:

	typedef std::map<std::string, Bone*> Map;

	Map _map;
		// ���� �����������
};
