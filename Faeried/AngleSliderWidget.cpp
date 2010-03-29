#include "AngleSliderWidget.h"

#include "Bone.h"

AngleSliderWidget::AngleSliderWidget(Bone*)
	: QSlider(Qt::Horizontal)
{
	setRange(-180, 180);
	setValue(0);
	//connect(this, SIGNAL(valueChanged(int)), bone, SLOT(SetAngleInDegrees(int))); 
	//connect(bone, SIGNAL(AngleInDegreesChanged(int)), this, SLOT(setValue(int)));
}