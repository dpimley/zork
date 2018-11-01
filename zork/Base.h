#ifndef BASE_H
#define BASE_H

#include <iostream>

#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"

#define NAME "name"
#define STATUS "status"
#define TYPE "type"
#define DESCRIPTION "description"
#define TURN_ON "turnon"
#define TRIGGER "trigger"
#define ACCEPT "accept"
#define ITEM "item"
#define ATTACK "attack"
#define VULNERABILITY "vulnerability"
#define WRITING "writing"
#define PRINT "print"
#define ACTION "action"
#define COMMAND "command"
#define CONDITION "condition"
#define HAS	"has"
#define OBJECT "object"
#define OWNER "owner"
#define DIRECTION "direction"
#define BORDER "border"
#define CONTAINER "container"
#define CREATURE "creature"

using namespace rapidxml;
using namespace std;

class Base {
public:
	Base();
	virtual ~Base();
};

#endif /* BASE_H */