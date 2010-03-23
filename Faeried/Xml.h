#pragma once

#include <iostream>
#include <fstream>

#include "Bool.h"
#include "rapidxml/rapidxml.hpp"

//
// ��������� ��� ����� ������� ������ � rapidxml
//
namespace Xml {

//
// �������
//
typedef rapidxml::xml_node<char> Node;

//
// �������
//
typedef rapidxml::xml_attribute<char> Attribute;

//
// XML-��������
// ������������ ������� ��������� ������
//
class Document
	: public rapidxml::xml_document<char>
{

private:
	
	char* _memblock;
		// ���� ������, � ������� ������� ����� xml
		// (����� ������� �� ������� ����������� ������� ���������)

public:

	//
	// �����������
	//
	Document(std::string filename)
		: rapidxml::xml_document<char>()
	{
		std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
		assert(file.is_open());
		size_t size = file.tellg();
		_memblock = new char [size + 1];
		file.seekg(0, std::ios::beg);
		file.read(_memblock, size);
		file.close();
		_memblock[size] = '\0';
		parse<0>(_memblock);
	}

	//
	// ����������
	// 
	~Document() {
		delete[] _memblock;
	}
};

//
// ������� ������� �������. ������� ������ ������������
//
inline bool GetBoolAttribute(Node* node, std::string attributeName) {
	Attribute* attribute = node->first_attribute(attributeName.c_str());
	assert(attribute != NULL);
	return Bool::Parse(attribute->value());
}

} // namespace Xml
