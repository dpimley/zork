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

	string type = "";
	vector<Border *> borders;
	vector<Container *> containers;
	vector<Item *> items;
	vector<Creature *> creatures;
};

#endif /* ROOM_H */