#include "BonesMap.h"
#include <assert.h>

void BonesMap::AddBone(std::string boneName, Bone* bone) {
	assert(find(boneName) == end());
	(*this)[boneName] = bone;
}

Bone* BonesMap::GetBone(std::string boneName) {
	assert(find(boneName) != end());
	return (*this)[boneName];
}

