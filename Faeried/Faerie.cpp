#include "Faerie.h"

#include <hge.h>
#include <hgesprite.h>

#include "Bone.h"
#include "FaerieAnimation.h"
#include "Xml.h"

Faerie::Faerie(HGE* hge)
	: _state(STATE_NOFRAME)
	, _draggingBone(NULL)
{
	Xml::ReadDocument doc("bones.xml");
	Xml::Node* rootXml = doc.first_node();
	assert(rootXml != NULL);
	assert(rootXml->first_node() != NULL);
	_rootBone = new Bone(hge, rootXml->first_node("bone"), &_bonesMap);
}

void Faerie::Draw(int x, int y) {
	if (_state == STATE_NOFRAME) {
		return;
	}
	_rootBone->Draw(FPoint(x, y), 0.0f);
}

void Faerie::Update(float dt) {
	if (_state == STATE_NOFRAME) {
		return;
	}
	if (_state == STATE_ANIMATION) {
		_animationTimer += dt;
		GuiChangedFrame(_animation->GetFrame(_animationTimer));
		emit SetAnimationProgress(fmod(_animationTimer, _animation->GetTime()) / _animation->GetTime());
	}
}

Bone* Faerie::GetBoneByName(std::string boneName) {
	return _bonesMap.GetBone(boneName);
}

void Faerie::OnMouseMove(Point p) {
	if (_state == STATE_NOFRAME) {
		return;
	}
	if (_state == STATE_ANIMATION) {
		return;
	}
	if (_state == STATE_SINGLE_FRAME) {
		_rootBone->GetBoneUnderMouse(p, FPoint(0, 0), 0.0f);
	} else if (_state == STATE_DRAGGING_BONE) {
		_draggingBone->Drag(p);
		emit FaerieChangedFrameSignal(CreateFrame());
	}
}

void Faerie::OnLeftMouseDown(Point p) {
	if (_state == STATE_NOFRAME) {
		return;
	}
	if (_state == STATE_ANIMATION) {
		return;
	}
	_draggingBone = _rootBone->GetBoneUnderMouse(p, FPoint(0, 0), 0.0f);
	if (_draggingBone != NULL) {
		_state = STATE_DRAGGING_BONE;
	}
}

void Faerie::OnLeftMouseUp(Point p) {
	if (_state == STATE_NOFRAME) {
		return;
	}
	if (_state == STATE_ANIMATION) {
		return;
	}
	if (_state == STATE_DRAGGING_BONE) {
		_draggingBone->Drag(p);
		emit FaerieChangedFrameSignal(CreateFrame());
		_draggingBone->FinishDragging();
		_draggingBone = NULL;
		_state = STATE_SINGLE_FRAME;
	}
}

void Faerie::GuiChangedFrame(FaerieFrame frame) {
	// передать в каждую кость угол, установить координаты
	for (BonesMap::iterator i = _bonesMap.begin(); i != _bonesMap.end(); ++i) {
		std::string boneName = i->first;
		Bone* bone = i->second;
		bone->SetAngleInDegrees(frame.GetBoneAngle(boneName));
	}
	_rootBone->SetInParentPos(frame.GetShift());
}

FaerieFrame Faerie::CreateFrame() {
	FaerieFrame frame;
	for (BonesMap::iterator i = _bonesMap.begin(); i != _bonesMap.end(); ++i) {
		std::string boneName = i->first;
		Bone* bone = i->second;
		frame.SetBoneAngle(boneName, bone->GetAngleInDegrees());
	}
	frame.SetShift(_rootBone->GetInParentPos());
	return frame;
}

void Faerie::SlotShowFaerie(bool doShow) {
	if (doShow) {
		_state = STATE_SINGLE_FRAME;
	} else {
		_state = STATE_NOFRAME;
	}
}

void Faerie::StartAnimationSlot(FaerieAnimation* animation) {
	assert(_state == STATE_SINGLE_FRAME);
	_state = STATE_ANIMATION;
	_animationTimer = 0.0f;
	_animation = animation;
}

void Faerie::StopAnimationSlot() {
	assert(_state == STATE_ANIMATION);
	_state = STATE_SINGLE_FRAME;
}
