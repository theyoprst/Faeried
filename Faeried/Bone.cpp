#include "Bone.h"

#include <hge.h>
#include <hgesprite.h>

#include "BonesMap.h"

Bone::Bone(HGE* hge, Xml::Node* boneXml, BonesMap* bonesMap)
	: QObject()
	, _inParentPosition(0, 0)
	, _rotationPoint(0, 0)
	, _angle(0.0f)
{
	assert(boneXml != NULL);
	
	_name = boneXml->first_attribute("name")->value();
	bonesMap->AddBone(_name, this);

	Xml::Node* textureXml = boneXml->first_node("texture");
	assert(textureXml != NULL);
	assert(textureXml->first_attribute("path") != NULL);
	HTEXTURE texture = hge->Texture_Load(textureXml->first_attribute("path")->value());
	int width = hge->Texture_GetWidth(texture);
	int height = hge->Texture_GetHeight(texture);
	_sprite = new hgeSprite(texture, 0.0f, 0.0f, (float)width, (float)height);

	Xml::Node* parentPointXml = boneXml->first_node("parentPoint");
	assert(parentPointXml != NULL);
	_inParentPosition = Point(parentPointXml);

	Xml::Node* rotationPointXml = boneXml->first_node("rotationPoint");
	assert(rotationPointXml != NULL);
	_rotationPoint = Point(rotationPointXml);
	_sprite->SetHotSpot(float(_rotationPoint.x), float(_rotationPoint.y));

	Xml::Node* childBoneXml = boneXml->first_node("bone");
	while (childBoneXml != NULL) {
		_children.push_back(new Bone(hge, childBoneXml, bonesMap));
		childBoneXml = childBoneXml->next_sibling("bone");
	}
}

void Bone::Draw(FPoint parentLeftTopCorner, float parentAngle) {
	FPoint rotationCenterPos = parentLeftTopCorner + FPoint(_inParentPosition).Rotate(parentAngle);
	//Point rotationCenterPos = parentLeftTopCorner + _inParentPosition;
	FPoint leftTopCorner = rotationCenterPos + FPoint(-_rotationPoint).Rotate(parentAngle + _angle);
	//Point leftTopCorner = rotationCenterPos - _rotationPoint;
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		(*i)->Draw(leftTopCorner, parentAngle + _angle);
	}
	_sprite->RenderEx(rotationCenterPos.x, rotationCenterPos.y, parentAngle + _angle);
}

void Bone::SetAngleInDegrees(int angleInDegrees) {
	_angle = angleInDegrees * Math::PI / 180.0f;
}
