#pragma once

#include "rapidxml/rapidxml.hpp"
#include <iostream>
#include <fstream>

//
// Структуры для более удобной работы с rapidxml
//
namespace Xml {

//
// Элемент
//
typedef rapidxml::xml_node<char> Node;

//
// Атрибут
//
typedef rapidxml::xml_attribute<char> Attribute;

//
// XML-документ
// Поддерживает удобный интерфейс чтения
//
class Document
	: public rapidxml::xml_document<char>
{

private:
	
	char* _memblock;
		// блок памяти, в котором записан текст xml
		// (нужно хранить до момента уничтожения объекта документа)

public:

	//
	// Конструктор
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
	// Деструктор
	// 
	~Document() {
		delete[] _memblock;
	}
};

} // namespace Xml
