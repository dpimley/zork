#ifndef ITEM_H
#define ITEM_H

#include "Base.h"

class Item : public Base{
public:
	Item(xml_node<> * acc);
	virtual ~Item();

	string name = "";
	string status = "";
	string description = "";
	string writing = "";
	string turn_on_print = "";
	string turn_on_action = "";
	string owner = "";
};

#endif /* ITEM_H */