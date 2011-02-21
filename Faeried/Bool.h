#pragma once

#include <string>
#include <assert.h>

class Bool {

public:

	//
	// Перевод из строки в булев тип
	//
	static bool Parse(std::string image) {
		if (image == "true") {
			return true;
		} else if (image == "false") {
			return false;
		} else {
			assert(false);
		}
		return false;
	}

};