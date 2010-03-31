#include "FaerieAnimation.h"

FaerieAnimation::FaerieAnimation(Xml::Node* element)
{
	_name = Xml::GetStringAttribute(element, "name");
	_time = Xml::GetFloatAttribute(element, "time");
	Xml::Node* keyFrameXml = element->first_node("keyFrame");
	while (keyFrameXml != NULL) {
		_keyFrames.push_back(FaerieFrame(keyFrameXml));
		keyFrameXml = keyFrameXml->next_sibling("keyFrame");
	}
}

FaerieAnimation::FaerieAnimation(std::string name)
	: _name(name)
	, _time(5.0f)
{
	_keyFrames.push_back(FaerieFrame());
}

FaerieFrame FaerieAnimation::GetFrame(float t) {
	assert(0.0f <= t && t <= 1.0f);
	FaerieFrame::BonesDegrees bonesDegrees;
	for (AngleSplines::iterator i = _angleSplines.begin(); i != _angleSplines.end(); ++i) {
		bonesDegrees[i->first] = i->second.getGlobalFrame(t);
	}
	FPoint shift(_xSpline.getGlobalFrame(t), _ySpline.getGlobalFrame(t));
	return FaerieFrame(bonesDegrees, shift);
}

void FaerieAnimation::FillXml(Xml::Document* document, Xml::Node* element) {
	Xml::SetStringAttribute(document, element, "name", _name);
	Xml::SetFloatAttribute(document, element, "time", _time);
	for (KeyFrames::iterator i = _keyFrames.begin(); i != _keyFrames.end(); ++i) {
		i->FillXml(document, Xml::AddElement(document, element, "keyFrame"));
	}
}

void FaerieAnimation::AddFrameToSpline(size_t frameNumber, const FaerieFrame& frame) {
	float time = static_cast<float>(frameNumber) / _keyFrames.size();
	const FaerieFrame::BonesDegrees& degrees = frame.GetBonesDegrees();
	for (FaerieFrame::BonesDegrees::const_iterator bone = degrees.begin(); bone != degrees.end(); ++bone) {
		_angleSplines[bone->first].addKey(time, bone->second);
	}
	FPoint shift = frame.GetShift();
	_xSpline.addKey(time, shift.x);
	_ySpline.addKey(time, shift.y);
}

void FaerieAnimation::CreateAnimationSplines() {
	int frameNumber = 0;
	_angleSplines.clear();
	_xSpline.clear();
	_ySpline.clear();
	assert(_keyFrames.size() > 0);
	for (KeyFrames::iterator i = _keyFrames.begin(); i != _keyFrames.end(); ++i) {
		AddFrameToSpline(frameNumber, *i);
		++frameNumber;
	}
	AddFrameToSpline(_keyFrames.size(), _keyFrames.front());
	
	// Calculate Gradients
	for (AngleSplines::iterator i = _angleSplines.begin(); i != _angleSplines.end(); ++i) {
		i->second.CalculateGradient();
	}
	_xSpline.CalculateGradient();
	_ySpline.CalculateGradient();
}

std::string FaerieAnimation::GetName() {
	return _name;
}

float FaerieAnimation::GetTime() {
	return _time;
}

void FaerieAnimation::SetTime(float time) {
	assert(time > 0.0f);
	_time = time;
}

int FaerieAnimation::GetFramesNumber() {
	return static_cast<int>(_keyFrames.size());
}

void FaerieAnimation::CloneFrame(int frameNumber) {
	assert(0 <= frameNumber && frameNumber < static_cast<int>(_keyFrames.size()));
	KeyFrames::iterator frame = _keyFrames.begin();
	std::advance(frame, frameNumber);
	KeyFrames::iterator frameNext = frame;
	std::advance(frameNext, 1);
	_keyFrames.insert(frameNext, *frame);
}

void FaerieAnimation::DeleteFrame(int frameNumber) {
	assert(0 <= frameNumber && frameNumber < static_cast<int>(_keyFrames.size()));
	KeyFrames::iterator frame = _keyFrames.begin();
	std::advance(frame, frameNumber);
	_keyFrames.erase(frame);
}