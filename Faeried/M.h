#pragma once

#include <assert.h>

namespace Math {
	
	const static float PI = 3.14526f;

	//
	// Rounds float f to int.
	//
	static int Round(float f) {
		if (f > 0.0f) {
			return (int)(f + 0.5f);
		} else {
			return (int)(f - 0.5f);
		}
	}

}
