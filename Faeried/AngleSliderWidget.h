#pragma once

#include <QtGui/QSlider>

class Bone;

//
// Виджет изменения угла
//
class AngleSliderWidget
	: public QSlider
{

public:

	//
	// Конструктор
	//
	explicit AngleSliderWidget(Bone* bone);

private:

};