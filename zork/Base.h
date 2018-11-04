#ifndef BASE_H
#define BASE_H

#include <iostream>

#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"

#include "Trigger.h"

#define NAME string("name")
#define STATUS string("status")
#define TYPE string("type")
#define DESCRIPTION string("description")
#define TURN_ON string("turnon")
#define TRIGGER string("trigger")
#define ACCEPT string("accept")
#define ITEM string("item")
#define ATTACK string("attack")
#define VULNERABILITY string("vulnerability")
#define WRITING string("writing")
#define PRINT string("print")
#define ACTION string("action")
#define COMMAND string("command")
#define CONDITION string("condition")
#define HAS	string("has")
#define OBJECT string("object")
#define OWNER string("owner")
#define DIRECTION string("direction")
#define BORDER string("border")
#define CONTAINER string("container")
#define CREATURE string("creature")
#define MAP string("map")
#define ROOM string("room")

using namespace rapidxml;
using namespace std;

class Base {
public:
	Base();
	virtual ~Base();

	Trigger * searchTriggers(string cur_command);

	vector<Trigger *> triggers;
};

#endif /* BASE_H */