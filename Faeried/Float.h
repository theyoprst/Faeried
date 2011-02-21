#pragma once

//#include <stdio.h>
//#include <cstdio>

class Float {

public:

	static float Parse(std::string image) {
		float result;
		sscanf_s(image.c_str(), "%f", &result);
		return result;
	}

	static std::string ToString(float value) {
		char result[64];
		sprintf_s(result, 64, "%f", value);
		return result;
	}
};
