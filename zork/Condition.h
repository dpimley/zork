#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>

#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"

#define TYPE string("type")
#define PRINT string("print")
#define ACTION string("action")
#define COMMAND string("command")
#define CONDITION string("condition")

using namespace rapidxml;
using namespace std;

class Condition {
public:
	Condition(xml_node<> * acc);
	virtual ~Condition();

	string has = "";
	string object = "";
	string owner = "";
	string status = "";
};

#endif /* CONDITION_H */