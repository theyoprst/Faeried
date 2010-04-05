#include "Bone.h"

#include <hge.h>
#include <hgesprite.h>

#include "BonesMap.h"

float Bone::_scale = 4.f;

Bone::Bone(HGE* hge, Xml::Node* boneXml, BonesMap* bonesMap)
	: QObject()
	, _inParentPosition(0, 0)
	, _rotationPoint(0, 0)
	, _angle(0.0f)
	, _hge(hge)
	, _state(STATE_NORMAL)
	, _isRoot(false)
	, _doNotLight(false)
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
	bool wasThis = false;
	while (childBoneXml != NULL) {
		if (childBoneXml->first_attribute("this") != NULL) {
			_children.push_back(this);
			wasThis = true;
		} else {
			_children.push_back(new Bone(hge, childBoneXml, bonesMap));
		}
		childBoneXml = childBoneXml->next_sibling("bone");
	}
	assert(wasThis);

	_isRoot = boneXml->first_attribute("root") != NULL;
}

void Bone::Draw(FPoint parentLeftTopCorner, float parentAngle) {
	FPoint rotationCenterPos = parentLeftTopCorner + FPoint(_inParentPosition).Scale(_scale).RotateCounterclockwise(parentAngle);
	FPoint leftTopCorner = rotationCenterPos + FPoint(-_rotationPoint).Scale(_scale).RotateCounterclockwise(parentAngle + _angle);
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		if (*i != this) {
			(*i)->Draw(leftTopCorner, parentAngle + _angle);
		} else {
			// сам себе ребенок
			if (_state == STATE_ROTATING && !_doNotLight) {
				_sprite->SetColor(0xFF00AA00);
			} else {
				_sprite->SetColor(0xFFFFFFFF);
			}
			// так как мы вращаем против часовой стрелки, а RenderEx вращает по, то инвертируем угол.
			_sprite->SetBlendMode(BLEND_DEFAULT);
			_sprite->RenderEx(rotationCenterPos.x, rotationCenterPos.y, - parentAngle - _angle, _scale);
			if (_state == STATE_MOVING) {
				_sprite->SetBlendMode(BLEND_ALPHAADD | BLEND_COLORADD | BLEND_NOZWRITE);
				_sprite->SetColor(0xFF0000AA);
				_sprite->RenderEx(rotationCenterPos.x, rotationCenterPos.y, - parentAngle - _angle, _scale);
			}
		}
	}
}

void Bone::SetAngleInDegrees(float angleInDegrees) {
	_angle = angleInDegrees * Math::PI / 180.0f;
}

void Bone::SetNotActiveRecursively() {
	_state = STATE_NORMAL;
	for (Children::iterator i = _children.begin(); i != _children.end(); ++i) {
		if (*i != this) {
			(*i)->SetNotActiveRecursively();
		}
	}
}

Bone* Bone::GetBoneUnderMouse(Point mouse, FPoint parentLeftTopCorner, float parentAngle) {
	Bone* underMouseBone = NULL; // результат
	FPoint rotationCenterPos = parentLeftTopCorner + FPoint(_inParentPosition).Scale(_scale).RotateCounterclockwise(parentAngle);
	FPoint leftTopCorner = rotationCenterPos + FPoint(-_rotationPoint).Scale(_scale).RotateCounterclockwise(parentAngle + _angle);

	// сначала проверяем детей, которые над родителем
	for (Children::reverse_iterator i = _children.rbegin(); i != _children.rend(); ++i) {
		if (*i != this) {
			if (underMouseBone == NULL) {
				underMouseBone = (*i)->GetBoneUnderMouse(mouse, leftTopCorner, parentAngle + _angle);
			} else {
				(*i)->SetNotActiveRecursively();
			}
		} else {
			// сам себе ребенок
			// мы знаем, что спрайт текстуры отрисовывается в точке rotationCenterPos под углом parentAngle + _angle против часовой
			// поэтому вращаем все назад (в том числе и координаты мыши) и проверяем принадлежность мыши к содержательному
			// прямоугольнику спрайта
			Point p = (FPoint(mouse) - rotationCenterPos).RotateClockwise(parentAngle + _angle).Divide(_scale).Round();
			hgeRect boundingBox;
			_sprite->GetBoundingBox(0, 0, &boundingBox);
			bool isActive = (underMouseBone == NULL) && boundingBox.TestPoint(p.x, p.y);
			if (isActive) {
				underMouseBone = this;
				if (_isRoot) {
					// Корневую кость не вращаем, а таскаем. Поэтому только запоминаем координаты мыши
					_state = STATE_MOVING;
					_dragMousePos = mouse;
					_dragInParentPosition = _inParentPosition.Round();
				} else {
					// Остальные кости вращаем, поэтому нам нужно запомнить чуть больше информации
					_state = STATE_ROTATING;
					_dragRotateCenter = rotationCenterPos;
					_dragRotatePoint1 = FPoint(mouse);
					_dragAngle1 = _angle;
					if (_dragRotatePoint1 == _dragRotateCenter) {
						// если мы кликаем прямо в центр вращения, то считаем что кликнули выше
						_dragRotatePoint1 += FPoint(0.0f, -1.0f);
					}
				}
			} else {
				_state = STATE_NORMAL;
			}
		}
	}
	if (underMouseBone == NULL && _isRoot) {
		// значит захватываем курсор и берем все на себя
		_state = STATE_ROTATING;
		_dragRotateCenter = rotationCenterPos;
		_dragRotatePoint1 = FPoint(mouse);
		_dragAngle1 = _angle;
		underMouseBone = this;
		_doNotLight = true;
	}
	return underMouseBone;
}

void Bone::Drag(Point p) {
	assert(_state != STATE_NORMAL);
	if (_state == STATE_MOVING) {
		// перетаскиваем
		_inParentPosition = _dragInParentPosition + FPoint(p - _dragMousePos).Scale(1 / _scale).Round();
	} else if (_state == STATE_ROTATING) {
		// вращаем
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
	} else {
		assert(false);
	}
	_doNotLight = false;
}

void Bone::FinishDragging() {
	assert(_state != STATE_NORMAL);
	_state = STATE_NORMAL;
}

float Bone::GetAngleInDegrees() {
	return _angle * 180 / Math::PI;
}

void Bone::SetInParentPos(FPoint pos) {
	_inParentPosition = pos;
}

FPoint Bone::GetInParentPos() {
	return _inParentPosition;
}

void Bone::SetScale(float newScale) {
	assert(newScale > 0);
	_scale = newScale;
}