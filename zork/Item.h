#ifndef ITEM_H
#define ITEM_H

#include "Base.h"

typedef struct _turn_on{
	string print;
	string action;
} turn_on;

class Item {
public:
	Item(xml_node<> * acc);
	virtual ~Item();

	string name = "";
	string status = "";
	string description = "";
	string status = "";
	_turn_on turn_on;
};

#endif /* ITEM_H */