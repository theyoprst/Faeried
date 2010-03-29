#include "AnimationsComboBox.h"

AnimationsComboBox::AnimationsComboBox(QWidget* parent)
	: QComboBox(parent)
{
}

void AnimationsComboBox::SetAnimationsList(const QStringList& texts) {
	clear();
	addItem(tr("<Выберите анимацию>"));
	addItems(texts);
}
