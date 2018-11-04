#ifndef ROOM_H
#define ROOM_H

#include "Base.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Border.h"

class Room : public Base{
public:
	Room(xml_node<> * acc);
	virtual ~Room();

	string name = "";
	string status = "";
	string type = "";
	string description = "";
	vector<Border *> borders;
	vector<Container *> containers;
	vector<Item *> items;
	vector<Creature *> creatures;
};

#endif /* ROOM_H */