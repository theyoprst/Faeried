#include "FaerieFrame.h"

FaerieFrame::FaerieFrame(Xml::Node* element)
{
	Xml::Node* bonesXml = element->first_node("bones");
	assert(bonesXml != NULL);
	Xml::Attribute* attributeXml = bonesXml->first_attribute();
	while (attributeXml != NULL) {
		std::string boneName = attributeXml->name();
		int angle = Int::Parse(attributeXml->value());
		assert(_bonesDegrees.find(boneName) == _bonesDegrees.end());
		_bonesDegrees[boneName] = angle;
		attributeXml = attributeXml->next_attribute();
	}
	Xml::Node* shiftXml = element->first_node("shift");
	assert(shiftXml != NULL);
	_shift = Point(shiftXml);
}

FaerieFrame::FaerieFrame(const BonesDegrees& bonesDegrees, FPoint shift)
	: _bonesDegrees(bonesDegrees)
	, _shift(shift)
{
}

FaerieFrame::FaerieFrame()
{
	_bonesDegrees["pelvis"] = 0;
	_bonesDegrees["leftThigh"] = 0;
	_bonesDegrees["leftLeg"] = 0;
	_bonesDegrees["rightThigh"] = 0;
	_bonesDegrees["rightLeg"] = 0;
	_bonesDegrees["body"] = 0;
	_bonesDegrees["head"] = 0;
	_bonesDegrees["leftArm"] = 0;
	_bonesDegrees["leftForearm"] = 0;
	_bonesDegrees["rightArm"] = 0;
	_bonesDegrees["rightForearm"] = 0;
}

void FaerieFrame::FillXml(Xml::Document* document, Xml::Node* element) {
	Xml::Node* bonesXml = Xml::AddElement(document, element, "bones");
	for (BonesDegrees::iterator i = _bonesDegrees.begin(); i != _bonesDegrees.end(); ++i) {
		Xml::SetIntAttribute(document, bonesXml, i->first, Math::Round(i->second));
	}
	Xml::Node* shiftXml = Xml::AddElement(document, element, "shift");
	Xml::SetIntAttribute(document, shiftXml, "x", Math::Round(_shift.x));
	Xml::SetIntAttribute(document, shiftXml, "y", Math::Round(_shift.y));
}

const FaerieFrame::BonesDegrees& FaerieFrame::GetBonesDegrees() const {
	return _bonesDegrees;
}

FPoint FaerieFrame::GetShift() const {
	return _shift;
}

void FaerieFrame::SetBoneAngle(std::string boneName, int angleInDegrees) {
	assert(_bonesDegrees.find(boneName) != _bonesDegrees.end());
	_bonesDegrees[boneName] = static_cast<float>(angleInDegrees);
}

void FaerieFrame::SetShift(FPoint shift) {
	_shift = shift;
}

float FaerieFrame::GetBoneAngle(std::string boneName) {
	assert(_bonesDegrees.find(boneName) != _bonesDegrees.end());
	return _bonesDegrees[boneName];
}

FPoint FaerieFrame::GetShift() {
	return _shift;
}
