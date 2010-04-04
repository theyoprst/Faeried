#pragma once

#include <map>
#include <string>

class Bone;

//
//  ласс отображени€ имени кости в указатель на неЄ
//
class BonesMap
	: public std::map<std::string, Bone*>
{

public:

	//
	// ƒобавить кость; если кость уже была добавлена, сработает ассерт
	//
	void AddBone(std::string boneName, Bone* bone);

	//
	// ѕолучить кость; если такой кости не было, сработает ассерт
	//
	Bone* GetBone(std::string boneName);

};
