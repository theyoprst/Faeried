#pragma once

#include <QtCore/QObject>

#include "FaerieFrame.h"
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
	// ������� ���������� ������ ������
	//
	void SetFramesList(const QStringList& list);

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

	//
	// ���������� ����� �������� �����
	//
	void SetCurrentFrame(int);

	//
	// ������ "���� �������� ����� gui"
	//
	void GuiChangedFrameSignal(FaerieFrame frame);

	//
	// ������ "���� �������� ����� ���"
	//
	void FaerieChangedFrameSignal(FaerieFrame frame);

	//
	// ������ ������ ��������
	//
	void StartAnimationSignal(FaerieAnimation* animation);

	//
	// ������ ��������� ��������
	//
	void StopAnimationSignal();

	//
	// ������ "�������� �� ��������"
	//
	void AnimationIsStopped(bool isStopped);

	//
	// ���������� �������� ��������
	//
	void SetAnimationProgress(float);

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

	//
	// ����������� ������� ����
	//
	void CloneCurrentFrame();

	//
	// ������� ������� ����
	//
	void DeleteCurrentFrame();

	//
	// ���� �������� ����� Gui
	//
	void GuiChangedFrame(FaerieFrame frame);

	//
	// ���� �������� ����� ���
	//
	void FaerieChangedFrame(FaerieFrame frame);

	//
	// ������ �� ������ ������ ��������
	//
	void StartAnimationSlot();

	//
	// ������ �� ������ ��������� ��������
	//
	void StopAnimationSlot();

private:

	FaerieAnimationsCollection* _collection;
		// ��������� ��������

	FaerieAnimation* _currentAnimation;
		// ��������� ��������

	int _currentFrameNumber;
		// ����� �������� �����

	//
	// ������� ������ ��������
	//
	QStringList GetAnimationsList();

	//
	// ���������������� ��� ������� ��������
	//
	void InitCurrentAnimationView();

	//
	// ������� ������ ������
	//
	QStringList GetFramesList();

};
