#include "AnimationsComboBox.h"

#include <assert.h>

AnimationsComboBox::AnimationsComboBox(QWidget* parent)
	: QComboBox(parent)
{
}

void AnimationsComboBox::SetAnimationsList(const QStringList& texts) {
	_animationNames = texts;
	clear();
	addItem(tr("<Выберите анимацию>"));
	addItems(texts);
}

void AnimationsComboBox::SetCurrentAnimationName(std::string animationName) {
	int index = _animationNames.indexOf(QString(animationName.c_str()));
	assert(index != -1);
	setCurrentIndex(index + 1);
}