#include "FaerieAnimationsDelegate.h"

#include <QtCore/QStringList>

#include "FaerieAnimationsCollection.h"
#include "types.h"

FaerieAnimationsDelegate::FaerieAnimationsDelegate(FaerieAnimationsCollection* collection)
	: _collection(collection)
	, _currentAnimation(NULL)
{
}

bool FaerieAnimationsDelegate::HasAnimation(std::string name) {
	return _collection->HasAnimation(name);
}

void FaerieAnimationsDelegate::AddAnimation(std::string name) {
	_currentAnimation = new FaerieAnimation(name);
	_collection->AddAnimation(new FaerieAnimation(name));
	emit SetAnimationsList(GetAnimationsList());
	emit SetCurrentAnimationName(name);
	emit AnimationIsSelected(true);
	InitCurrentAnimationView();
}

void FaerieAnimationsDelegate::DeleteCurrentAnimation() {
	assert(_currentAnimation != NULL);
	_collection->DeleteAnimation(_currentAnimation->GetName());
	emit SetAnimationsList(GetAnimationsList());
	emit AnimationIsSelected(false);
}

void FaerieAnimationsDelegate::InitView() {
	emit SetAnimationsList(GetAnimationsList());
}

QStringList FaerieAnimationsDelegate::GetAnimationsList() {
	StringVector names = _collection->GetAnimationsNames();
	QStringList animationsList;
	for (StringVector::iterator i = names.begin(); i != names.end(); ++i) {
		animationsList.push_back(tr(i->c_str()));
	}
	return animationsList;
}

void FaerieAnimationsDelegate::SetAnimationTime(double time) {
	assert(_currentAnimation != NULL);
	_currentAnimation->SetTime(float(time));
}

void FaerieAnimationsDelegate::SaveAll() {
	_collection->Store();
}

void FaerieAnimationsDelegate::DiscardAll() {
	InitView();
}

void FaerieAnimationsDelegate::SetCurrentFrameNumber(int frameNumber) {
}

void FaerieAnimationsDelegate::SetCurrentAnimation(const QString& name) {
	if (_collection->HasAnimation(name.toStdString())) {
		_currentAnimation = _collection->GetAnimation(name.toStdString());
		InitCurrentAnimationView();
	} else {
		_currentAnimation = NULL;
	}
	emit AnimationIsSelected(_currentAnimation != NULL);
}

void FaerieAnimationsDelegate::InitCurrentAnimationView() {
	assert(_currentAnimation != NULL);
	emit InitAnimationTime(double(_currentAnimation->GetTime()));
}