#include "Bone.h"

#include <hge.h>
#include <hgesprite.h>

#include "BonesMap.h"

Bone::Bone(HGE* hge, Xml::Node* boneXml, BonesMap* bonesMap)
	: QObject()
	, _inParentPosition(0, 0)
	, _rotationPoint(0, 0)
	, _angle(0.0f)
	, _hge(hge)
	, _isActive(false)
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
	_underParent = Xml::GetBoolAttribute(boneXml, "underParent");
}

void Bone::Draw(FPoint parentLeftTopCorner, float parentAngle) {
	FPoint rotationCenterPos = parentLeftTopCorner + FPoint(_inParentPosition).RotateCounterclockwise(parentAngle);
	FPoint leftTopCorner = rotationCenterPos + FPoint(-_rotationPoint).RotateCounterclockwise(parentAngle + _angle);
	
	// рисуем детей под родителем:
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		if ((*i)->IsUnderParent()) {
			(*i)->Draw(leftTopCorner, parentAngle + _angle);
		}
	}
	
	if (_isActive) {
		_sprite->SetColor(0xFF00AA00);
	} else {
		_sprite->SetColor(0xFFFFFFFF);
	}
	// так как мы вращаем против часовой стрелки, а RenderEx вращает по, то инвертируем угол.
	_sprite->RenderEx(rotationCenterPos.x, rotationCenterPos.y, - parentAngle - _angle);

	// рисуем детей над родителем:
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		if (!(*i)->IsUnderParent()) {
			(*i)->Draw(leftTopCorner, parentAngle + _angle);
		}
	}
}

void Bone::SetAngleInDegrees(int angleInDegrees) {
	_angle = angleInDegrees * Math::PI / 180.0f;
}


void Bone::SetNotActiveRecursively() {
	_isActive = false;
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		(*i)->SetNotActiveRecursively();
	}
}

Bone* Bone::GetBoneUnderMouse(Point mouse, FPoint parentLeftTopCorner, float parentAngle) {
	Bone* underMouseBone = NULL; // результат
	FPoint rotationCenterPos = parentLeftTopCorner + FPoint(_inParentPosition).RotateCounterclockwise(parentAngle);
	FPoint leftTopCorner = rotationCenterPos + FPoint(-_rotationPoint).RotateCounterclockwise(parentAngle + _angle);

	// сначала проверяем детей, которые над родителем
	for (Children::reverse_iterator i = _children.rbegin(); i != _children.rend(); ++i) {
		if (!(*i)->IsUnderParent()) {
			if (underMouseBone == NULL) {
				underMouseBone = (*i)->GetBoneUnderMouse(mouse, leftTopCorner, parentAngle + _angle);
			} else {
				(*i)->SetNotActiveRecursively();
			}
		}
	}

	// затем проверяем нашего родителя
	// мы знаем, что спрайт текстуры отрисовывается в точке rotationCenterPos под углом parentAngle + _angle против часовой
	// поэтому вращаем все назад (в том числе и координаты мыши) и проверяем принадлежность мыши к содержательному
	// прямоугольнику спрайта
	Point p = (FPoint(mouse) - rotationCenterPos).RotateClockwise(parentAngle + _angle).Round();
	hgeRect boundingBox;
	_sprite->GetBoundingBox(0, 0, &boundingBox);
	_isActive = (underMouseBone == NULL) && boundingBox.TestPoint(p.x, p.y);
	if (_isActive) {
		underMouseBone = this;
		_dragRotateCenter = rotationCenterPos;
		_dragRotatePoint1 = FPoint(mouse);
		_dragAngle1 = _angle;
		if (_dragRotatePoint1 == _dragRotateCenter) {
			// если мы кликаем прямо в центр вращения, то считаем что кликнули выше
			_dragRotatePoint1 += FPoint(0.0f, -1.0f);
		}
	}
	
	// Затем проверяем детей, которые под родителями
	for (Children::reverse_iterator i = _children.rbegin(); i != _children.rend(); ++i) {
		if ((*i)->IsUnderParent()) {
			if (underMouseBone == NULL) {
				underMouseBone = (*i)->GetBoneUnderMouse(mouse, leftTopCorner, parentAngle + _angle);
			} else {
				(*i)->SetNotActiveRecursively();
			}
		}
	}
	return underMouseBone;
}

void Bone::Drag(Point p) {
	assert(_isActive);
	FPoint dragRotatePoint2 = FPoint(p);
	if (dragRotatePoint2 == _dragRotateCenter) {
		dragRotatePoint2 += FPoint(0.0f, -1.0f);
	}
	// вычитаем, т.к. _angle - угол против часовой стрелки, а GetDirectedAngleTo возвращает угол по часовой стрелке
	_angle = _dragAngle1 - (_dragRotatePoint1 - _dragRotateCenter).GetDirectedAngleTo(dragRotatePoint2 - _dragRotateCenter);
	// теперь приводим угол к отрезку [-PI; PI] и посылаем сигнал об изменении угла
	while (_angle < -Math::PI) {
		_angle += Math::PI * 2;
	}
	while (_angle > +Math::PI) {
		_angle -= Math::PI * 2;
	}
	int angleInDegrees = Math::Round(_angle / Math::PI * 180.0f);
	emit AngleInDegreesChanged(angleInDegrees);
}

void Bone::FinishDragging() {
	_isActive = false;
}

bool Bone::IsUnderParent() {
	return _underParent;
}

