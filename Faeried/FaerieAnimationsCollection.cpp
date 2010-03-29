#include "FaerieAnimationsCollection.h"

FaerieAnimationsCollection::FaerieAnimationsCollection(std::string filename)
	: _filename(filename)
{
	Xml::ReadDocument doc(_filename);
	Xml::Node* rootNode = doc.first_node();
	assert(rootNode != NULL);
	Xml::Node* animationNode = rootNode->first_node("animation");
	while (animationNode != NULL) {
		FaerieAnimation* animation = new FaerieAnimation(animationNode);
		std::string animationName = animation->GetName();
		assert(_mapAnimations.find(animationName) == _mapAnimations.end());
		_mapAnimations[animationName] = animation;
		animationNode = animationNode->next_sibling("animation");
	}
}

void FaerieAnimationsCollection::Store() {
	Xml::Document document;
	Xml::Node* animationsXml = Xml::AddElement(&document, &document, "animations");
	for (MapAnimations::iterator i = _mapAnimations.begin(); i != _mapAnimations.end(); ++i) {
		Xml::Node* animationXml = Xml::AddElement(&document, animationsXml, "animation");
		i->second->FillXml(&document, animationXml);
	}
	Xml::StoreDocument(document, _filename);
}

FaerieAnimation* FaerieAnimationsCollection::GetAnimation(std::string animationName) {
	assert(_mapAnimations.find(animationName) != _mapAnimations.end());
	return _mapAnimations[animationName];
}

bool FaerieAnimationsCollection::HasAnimation(std::string animationName) {
	return _mapAnimations.find(animationName) != _mapAnimations.end();
}

void FaerieAnimationsCollection::AddAnimation(FaerieAnimation* animation) {
	assert(!HasAnimation(animation->GetName()));
	_mapAnimations[animation->GetName()] = animation;
}

void FaerieAnimationsCollection::DeleteAnimation(std::string animationName) {
	MapAnimations::iterator i = _mapAnimations.find(animationName);
	assert(i != _mapAnimations.end());
	_mapAnimations.erase(i);
}

StringVector FaerieAnimationsCollection::GetAnimationsNames() {
	StringVector result;
	for (MapAnimations::iterator i = _mapAnimations.begin(); i != _mapAnimations.end(); ++i) {
		result.push_back(i->first);
	}
	return result;
}
