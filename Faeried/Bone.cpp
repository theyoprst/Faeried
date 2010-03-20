#include "Bone.h"

#include <hge.h>
#include <hgesprite.h>

#include "Xml.h"

Bone::Bone(HGE* hge, rapidxml::xml_node<char>* boneXml)
	: _inParentPosition(0, 0)
	, _rotationPoint(0, 0)
{
	assert(boneXml != NULL);
	
	_name = boneXml->first_attribute("name")->name();
	
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
		_children.push_back(new Bone(hge, childBoneXml));
		childBoneXml = childBoneXml->next_sibling("bone");
	}
}

void Bone::Draw(Point parentLeftTopCorner) {
	Point rotationCenterPos = parentLeftTopCorner + _inParentPosition;
	Point leftTopCorner = rotationCenterPos - _rotationPoint;
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		(*i)->Draw(leftTopCorner);
	}
	_sprite->Render(rotationCenterPos.x, rotationCenterPos.y);
}
