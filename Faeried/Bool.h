#pragma once

class Bool {

public:

	//
	// ������� �� ������ � ����� ���
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