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
	emit SetFramesList(GetFramesList());
	emit SetCurrentFrame(0);
	_currentFrameNumber = 0;
}

QStringList FaerieAnimationsDelegate::GetFramesList() {
	QStringList frames;
	for (int i = 0; i < _currentAnimation->GetFramesNumber(); ++i) {
		frames.push_back(tr("Frame") + Int::ToQString(i));
	}
	return frames;
}

void FaerieAnimationsDelegate::CloneCurrentFrame() {
	assert(_currentAnimation != NULL);
	_currentAnimation->CloneFrame(_currentFrameNumber);
	int currentFrameNumber = _currentFrameNumber + 1;
	emit SetFramesList(GetFramesList());
	emit SetCurrentFrame(currentFrameNumber);
}

void FaerieAnimationsDelegate::SetCurrentFrameNumber(int frameNumber) {
	assert(_currentAnimation != NULL);
	_currentFrameNumber = frameNumber;
	if (frameNumber != -1) {
		emit GuiChangedFrameSignal(_currentAnimation->GetKeyFrame(_currentFrameNumber));
		emit FaerieChangedFrameSignal(_currentAnimation->GetKeyFrame(_currentFrameNumber));
	}
}

void FaerieAnimationsDelegate::DeleteCurrentFrame() {
	assert(_currentAnimation != NULL);
	_currentAnimation->DeleteFrame(_currentFrameNumber);
	int currentFrameNumber = _currentFrameNumber;
	QStringList frames = GetFramesList();
	if (currentFrameNumber >= frames.size()) {
		currentFrameNumber = frames.size() - 1;
	}
	emit SetFramesList(frames);
	emit SetCurrentFrame(currentFrameNumber);
}

void FaerieAnimationsDelegate::GuiChangedFrame(FaerieFrame frame) {
	assert(_currentAnimation != NULL);
	_currentAnimation->SetKeyFrame(_currentFrameNumber, frame);
	emit GuiChangedFrameSignal(frame);
}

void FaerieAnimationsDelegate::FaerieChangedFrame(FaerieFrame frame) {
	assert(_currentAnimation != NULL);
	emit FaerieChangedFrameSignal(frame);
	_currentAnimation->SetKeyFrame(_currentFrameNumber, frame);
}
