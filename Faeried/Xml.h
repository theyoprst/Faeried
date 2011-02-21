#pragma once

#include <iostream>
#include <fstream>

#include "Bool.h"
#include "Float.h"
#include "rapidxml/rapidxml.hpp"

#pragma warning(push)
#pragma warning(disable : 4100)
#include "rapidxml/rapidxml_print.hpp"
#pragma warning(pop)

//
// Структуры для более удобной работы с rapidxml
//
namespace Xml {

//
// Документ
//
typedef rapidxml::xml_document<> Document;

//
// Элемент
//
typedef rapidxml::xml_node<> Node;

//
// Атрибут
//
typedef rapidxml::xml_attribute<> Attribute;

//
// XML-документ
// Поддерживает удобный интерфейс чтения
//
class ReadDocument
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
	ReadDocument(std::string filename)
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
	~ReadDocument() {
		delete[] _memblock;
	}
}; // class ReadDocument

//
// Записать документ
//
static void StoreDocument(Document& document, std::string filename) {
	std::ofstream file(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	assert(file.is_open());
	file << document;
	file.close();
}

//
// Вернуть строковый атрибут. Атрибут обязан существовать.
//
static std::string GetStringAttribute(Node* node, std::string attributeName) {
	Attribute* attribute = node->first_attribute(attributeName.c_str());
	assert(attribute != NULL);
	return attribute->value();
}

//
// Добавить элемент с именем name
//
static Node* AddElement(Document* document, Node* parent, std::string name) {
	char* allocatedName = document->allocate_string(name.c_str());
	Node* element = document->allocate_node(rapidxml::node_element, allocatedName);
	parent->append_node(element);
	return element;
}

//
// Установить строковый атрибут с именем name и значением value
//
static Attribute* SetStringAttribute(Document* document, Node* parent, std::string name, std::string value) {
	char* allocatedName = document->allocate_string(name.c_str());
	char* allocatedValue = document->allocate_string(value.c_str());
	Attribute* attribute = document->allocate_attribute(allocatedName, allocatedValue);
	parent->append_attribute(attribute);
	return attribute;
}

//
// Установить целочисленный атрибут с именем name и значением value
//
static Attribute* SetIntAttribute(Document* document, Node* parent, std::string name, int value) {
	return SetStringAttribute(document, parent, name, Int::ToString(value));
}

//
// Установить float атрибут с именем name и значением value
//
static Attribute* SetFloatAttribute(Document* document, Node* parent, std::string name, float value) {
	return SetStringAttribute(document, parent, name, Float::ToString(value));
}

//
// Вернуть булевый атрибут. Атрибут обязан существовать.
//
static bool GetBoolAttribute(Node* node, std::string attributeName) {
	return Bool::Parse(GetStringAttribute(node, attributeName));
}

//
// Вернуть float атрибут. Атрибут обязан существовать
//
static float GetFloatAttribute(Node* node, std::string attributeName) {
	return Float::Parse(GetStringAttribute(node, attributeName));
}

} // namespace Xml
