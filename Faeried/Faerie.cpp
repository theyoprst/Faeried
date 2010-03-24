#include "Faerie.h"

#include <hge.h>
#include <hgesprite.h>

#include "Bone.h"
#include "Xml.h"

Faerie::Faerie(HGE* hge)
	: _state(STATE_WAITING)
	, _draggingBone(NULL)
{
	Xml::Document doc("bones.xml");
	Xml::Node* rootXml = doc.first_node();
	assert(rootXml != NULL);
	assert(rootXml->first_node() != NULL);
	_rootBone = new Bone(hge, rootXml->first_node("bone"), &_bonesMap);
}

void Faerie::Draw(int x, int y) {
	_rootBone->Draw(FPoint(x, y), 0.0f);
}

void Faerie::Update(float dt) {
}

Bone* Faerie::GetBoneByName(std::string boneName) {
	return _bonesMap.GetBone(boneName);
}

void Faerie::OnMouseMove(Point p) {
	if (_state == STATE_WAITING) {
		_rootBone->GetBoneUnderMouse(p, FPoint(0, 0), 0.0f);
	} else if (_state == STATE_DRAGGING_BONE) {
		_draggingBone->Drag(p);
	}
}

void Faerie::OnLeftMouseDown(Point p) {
	_draggingBone = _rootBone->GetBoneUnderMouse(p, FPoint(0, 0), 0.0f);
	if (_draggingBone != NULL) {
		_state = STATE_DRAGGING_BONE;
	}
}

void Faerie::OnLeftMouseUp(Point p) {
	if (_state == STATE_DRAGGING_BONE) {
		_draggingBone->Drag(p);
		_draggingBone->FinishDragging();
		_draggingBone = NULL;
		_state = STATE_WAITING;
	}
}