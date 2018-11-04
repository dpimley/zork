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
	Creature * getCreature(string cr_name);
	Container * getContainer(string co_name);
	Item * getItem(string i_name);
	Room * switchRoom(string cmd, Room * cur_room);
	Item * searchInventory(string i_name);

	void printContainerItems(Container * cont);

	unsigned char determineStatus(Trigger * trig);

	void initItems();

	Trigger * getReadyTriggers(Room * cur_room, string cur_command);

	void runNCTriggers(Room * cur_room);

	void runTrigger(Trigger * trig);

	vector<string> split(string in, char delim);

	unsigned char validateCommand(string cur_command);

	void actionExecute(string action);

	Base * searchAll(string o_name);

	void actionDelete(string o_name);

	vector<Item *> inventory;

	xml_node<> * map;
	vector<Room *> rooms;
	vector<Item *> items;
	vector<Container *> containers;
	vector<Creature *> creatures;
	unsigned char end_game = 0;
};

#endif /* GAME_H */