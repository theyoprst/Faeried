#pragma once

#include <assert.h>
#include <QtCore/QString>

//
// ������ �������� ��� ������ �������
//
class Int {

public:

	//
	// ������ ����� �� ������
	//
	static int Parse(const char* s) {
		assert(*s != '\0');
		float multiplier = 1;
		if (*s == '-') {
			multiplier = -1;
			*s++;
		}
		assert(*s != '\0');
		int result = 0;
		while (*s != '\0') {
			int d = *s - '0';
			assert(0 <= d && d <= 9);
			result = result * 10 + d;
			s++;
		}
		return multiplier * result;
	}

	//
	// ������� ����� � ������
	//
	static std::string ToString(int n) {
		char buf[32];
		sprintf_s(buf, "%d", n);
		return buf;
	}

	//
	// ������� ����� � QString
	//
	static QString ToQString(int n) {
		return QString(ToString(n).c_str());
	}

};