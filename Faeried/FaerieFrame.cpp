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
