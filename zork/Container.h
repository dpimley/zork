#ifndef CONTAINER_H
#define CONTAINER_H

#include "Base.h"
#include "Item.h"

class Container : public Base {
public:
	Container(xml_node<> * acc);
	virtual ~Container();

	string name = "";
	string status = "";
	string description = "";
	vector<string> accept;
	vector<Item *> items;
};

#endif /* CONTAINER_H */