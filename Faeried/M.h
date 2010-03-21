#pragma once

#include <assert.h>

namespace Math {
	
	const static float PI = 3.14526f;

	//
	// Parses number from null-terminating string
	//
	static int ParseInt(const char* s) {
		int result = 0;
		assert(*s != '\0');
		while (*s != '\0') {
			int d = *s - '0';
			assert(0 <= d && d <= 9);
			result = result * 10 + d;
			s++;
		}
		return result;
	}

}
