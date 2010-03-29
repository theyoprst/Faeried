#pragma once

#include <QtCore/QObject>

class FaerieAnimation;
class FaerieAnimationsCollection;

//
// �����, ��������������� ����������� �� �������� ������������� �
// ���������� � ������������ � ����� ���������� ��������
//
class FaerieAnimationsDelegate
	: public QObject
{

	Q_OBJECT

public:

	//
	// �����������
	//
	explicit FaerieAnimationsDelegate(FaerieAnimationsCollection* collection);

	//
	// ���� �� �������� � ����� ������
	//
	bool HasAnimation(std::string name);

	//
	// �������� �������� � ����� ������
	//
	void AddAnimation(std::string name);

	//
	// ������� ������� ��������
	//
	void DeleteCurrentAnimation();

	//
	// ���������������� ��� ���������
	//
	void InitView();

signals:

	//
	// �������, ����������, ����� ����� ���������������� ������ ��������
	//
	void SetAnimationsList(const QStringList& list);

	//
	// ������� ������� �������� / �������� �� �������
	//
	void AnimationIsSelected(bool isAnimationSelected);

	//
	// ������� ���������������� ����� ���������
	//
	void InitAnimationTime(float time);

	//
	// ���������� ������������� ������� ��������
	//
	void SetCurrentAnimation(std::string);

public slots:

	//
	// ���������� ����� ��������
	//
	void SetAnimationTime(float time);

	//
	// ��������� ��� ��������
	//
	void SaveAll();

	//
	// �������� ��� ��������� � ���������
	//
	void DiscardAll();

	//
	// ���������� ����� �������� ����� ���� ��������������
	//
	void SetCurrentFrameNumber(int number);

private:

	//
	// ������� ������ ��������
	//
	QStringList GetAnimationsList();

	FaerieAnimationsCollection* _collection;
		// ��������� ��������

	FaerieAnimation* _currentAnimation;
		// ��������� ��������
};
