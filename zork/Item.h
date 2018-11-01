#ifndef ITEM_H
#define ITEM_H

#include "Base.h"
#include "Trigger.h"

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
	string writing = "";
	_turn_on turn_on;
	vector<Trigger *> triggers;
};

#endif /* ITEM_H */