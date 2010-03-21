#include "BonesMap.h"
#include <assert.h>

void BonesMap::AddBone(std::string boneName, Bone* bone) {
	assert(_map.find(boneName) == _map.end());
	_map[boneName] = bone;
}

Bone* BonesMap::GetBone(std::string boneName) {
	assert(_map.find(boneName) != _map.end());
	return _map[boneName];
}

