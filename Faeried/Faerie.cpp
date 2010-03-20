#include "Faerie.h"

#include <hge.h>
#include <hgesprite.h>

#include "Bone.h"
#include "Xml.h"

Faerie::Faerie(HGE* hge)
{
	Xml::Document doc("bones.xml");
	Xml::Node* rootXml = doc.first_node();
	assert(rootXml != NULL);
	assert(rootXml->first_node() != NULL);
	_rootBone = new Bone(hge, rootXml->first_node("bone"));
}

void Faerie::Draw() {
	_rootBone->Draw(Point(0, 0));
}

void Faerie::Update(float dt) {
}