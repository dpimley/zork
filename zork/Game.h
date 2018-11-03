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

	void start();
	void printObjects();
	void printInventory();
	Room * getRoom(string r_name);
	Room * switchRoom(string cmd, string cur_room);

	vector<Item *> inventory;

	xml_node<> * map;
	vector<Room *> rooms;
	vector<Item *> items;
	vector<Container *> containers;
	vector<Creature *> creatures;
};

#endif /* GAME_H */