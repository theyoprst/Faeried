#pragma once

#include <QtGui/QSlider>

class Bone;

//
// ������ ��������� ����
//
class AngleSliderWidget
	: public QSlider
{

public:

	//
	// �����������
	//
	explicit AngleSliderWidget(Bone* bone);

private:

};