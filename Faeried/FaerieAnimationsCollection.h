#pragma once

#include <map>

#include "FaerieAnimation.h"
#include "types.h"

//
// �����-����� ��������.
// �������� �� ������ � ������ �������� �� ����
//
class FaerieAnimationsCollection
{
public:
	
	//
	// ������ � �����
	//
	FaerieAnimationsCollection(std::string filename);

	//
	// ������ �� ����
	//
	void Store();

	//
	// ������� ��������� �� ��������;
	// �������� � ����� ������ ������� ������������
	//
	FaerieAnimation* GetAnimation(std::string animationName);

	//
	// ���� �� ����� �������� � ���������
	//
	bool HasAnimation(std::string animationName);

	//
	// �������� �������� � ���������
	//
	void AddAnimation(FaerieAnimation* animation);

	//
	// ������� �������� �� ���������
	//
	void DeleteAnimation(std::string animationName);

	//
	// ������� ������ ���� ��������
	//
	StringVector GetAnimationsNames();

private:

	typedef std::map<std::string, FaerieAnimation*> MapAnimations;

	MapAnimations _mapAnimations;
		// ����������� "��� - ��������"

	std::string _filename;
		// ��� �����, ���������� ����� ��������� ���� ��
};
