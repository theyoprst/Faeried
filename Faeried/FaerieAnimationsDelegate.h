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
	void InitAnimationTime(double time);

	//
	// ���������� ������������� ������� ��������
	//
	void SetCurrentAnimationName(std::string);

public slots:

	//
	// ���������� ����� ��������
	//
	void SetAnimationTime(double time);

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

	//
	// ���������� ������� ��������
	//
	void SetCurrentAnimation(const QString& name);

private:

	FaerieAnimationsCollection* _collection;
		// ��������� ��������

	FaerieAnimation* _currentAnimation;
		// ��������� ��������

	//
	// ������� ������ ��������
	//
	QStringList GetAnimationsList();

	//
	// ���������������� ��� ������� ��������
	//
	void InitCurrentAnimationView();
};
