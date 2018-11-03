#include "Game.h"

Game::~Game() {}

Game::Game(string file) {
	xml_document<> doc;
	xml_node<> * root_node;

	std::ifstream theFile(file);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("map");

	xml_node<> * search_node = root_node;

	while (search_node != NULL){
		string cur_name = search_node->name();
		if (MAP == search_node->name()){
			map = search_node;
			search_node = search_node->first_node();
			continue;
		}
		else if (ROOM == search_node->name()){
			Room * _tmp_room = new Room(search_node);
			rooms.push_back(_tmp_room);
		}
		else if (ITEM == search_node->name()){
			Item * _tmp_item = new Item(search_node);
			items.push_back(_tmp_item);
		}
		else if (CONTAINER == search_node->name()){
			Container * _tmp_room = new Container(search_node);
			containers.push_back(_tmp_room);
		}
		else if (CREATURE == search_node->name()){
			Creature * _tmp_creature = new Creature(search_node);
			creatures.push_back(_tmp_creature);
		}
		search_node = search_node->next_sibling();
	}
}

void Game::start(){
	unsigned char end_game = 0;
	string input_line = "";
	string cur_command = "";

	Room * cur_room = getRoom("Entrance");
	if (NULL == cur_room){
		cout << "Game Over" << endl;
		return;
	}
	cout << cur_room->description << endl;

	while (!end_game){
		getline(cin, input_line);
		cur_command = input_line.substr(0, input_line.find(" "));

		if (string("i") == cur_command){
			printInventory();
		}
		else if (string("n") == cur_command || string("s") == cur_command
			|| string("e") == cur_command || string("w") == cur_command){

		}
	}
}

void Game::printObjects(){
	for (vector<Room *>::iterator itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room){
		cout << "Room Name: " << (*itr_room)->name << endl;
	}
	for (vector<Item *>::iterator itr_item = items.begin(); itr_item != items.end(); ++itr_item) {
		cout << "Item Name: " << (*itr_item)->name << endl;
	}
	for (vector<Container *>::iterator itr_container = containers.begin(); itr_container != containers.end(); ++itr_container) {
		cout << "Container Name: " << (*itr_container)->name << endl;
	}
	for (vector<Creature *>::iterator itr_creature = creatures.begin(); itr_creature != creatures.end(); ++itr_creature) {
		cout << "Creature Name: " << (*itr_creature)->name << endl;
	}
}

void Game::printInventory(){
	cout << "Inventory: ";
	vector<Item *>::iterator itr_inv = inventory.begin();
	for (itr_inv; itr_inv != inventory.end(); ++itr_inv){
		cout << (*itr_inv)->name;
	}
	cout << endl;
}

Room * Game::getRoom(string r_name){
	vector<Room *>::iterator itr_room = rooms.begin();
	while (itr_room != rooms.end() && (*itr_room)->name != r_name){
		++itr_room;
	}
	if ((*itr_room)->name == r_name){
		return (*itr_room);
	}
	else{
		return NULL;
	}
}

Room * Game::switchRoom(string cur_command, string cur_room){

}