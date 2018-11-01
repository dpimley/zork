#include "Game.h"

Game::~Game() {}

Game::Game(string file) {
	xml_document<> doc;
	xml_node<> * root_node;

	std::ifstream theFile(file);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node(MAP);

	xml_node<> * search_node = root_node->first_node(MAP);

	while (search_node != NULL){
		if (MAP == search_node->name){
			map = search_node;
		}
		else if (ROOM == search_node->name){
			Room * _tmp_room = new Room(search_node);
			rooms.push_back(_tmp_room);
		}
		else if (ITEM == search_node->name){
			Item * _tmp_item = new Item(search_node);
			items.push_back(_tmp_item);
		}
		else if (CONTAINER == search_node->name){
			Container * _tmp_room = new Container(search_node);
			containers.push_back(_tmp_room);
		}
		else if (CREATURE == search_node->name){
			Creature * _tmp_creature = new Creature(search_node);
			creatures.push_back(_tmp_creature);
		}
		search_node = search_node->next_sibling();
	}
}

void Game::printObjects(){

	for (itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room){

	}
}