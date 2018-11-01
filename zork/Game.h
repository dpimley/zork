#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"

class Game {
public:
	Game(string file);
	virtual ~Game();

	void printObjects();

	xml_node<> * map;
	vector<Room *> rooms;
	vector<Item *> items;
	vector<Container *> containers;
	vector<Creature *> creatures;
};

#endif /* GAME_H */