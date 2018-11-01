#ifndef ROOM_H
#define ROOM_H

#include "Base.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"

typedef struct _border{
	string direction;
	string name;
};

class Room {
public:
	Room(xml_node<> * acc);
	virtual ~Room();

	string name = "";
	string status = "";
	string type = "";
	string description = "";
	vector<_border *> borders;
	vector<Container *> containers;
	vector<Item *> items;
	vector<Creature *> creatures;
	vector<Trigger *> triggers;
};

#endif /* ROOM_H */