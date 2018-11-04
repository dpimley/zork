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
	initItems();
}

void Game::start(){
	unsigned char end_game = 0;
	string input_line = "";
	string cur_command = "";
	vector<string> user_in_split;
	Item * item_op = NULL;;
	Trigger * trigger_check = NULL;
	Container * container_check = NULL;
	Container * container_gl = NULL;
	unsigned char trig_priority = 0;
	unsigned char taken = 0;

	Room * cur_room = getRoom("Entrance");
	if (NULL == cur_room){
		cout << "Game Over" << endl;
		return;
	}
	cout << cur_room->description << endl;

	while (!end_game){
		getline(cin, input_line);
		cur_command = input_line.substr(0, input_line.find(" "));

		if (validateCommand(cur_command)){
			trigger_check = getReadyTriggers(cur_room, cur_command);
			if (trigger_check){
				runTrigger(trigger_check);
				trig_priority = 1;
			}
			else{
				trig_priority = 0;
			}

			if (!trig_priority){
				if (string("i") == cur_command){
					printInventory();
				}
				else if (string("n") == cur_command || string("s") == cur_command
					|| string("e") == cur_command || string("w") == cur_command){
					Room * next_room = switchRoom(cur_command, cur_room);
					if (NULL != next_room) {
						cur_room = next_room;
					}
				}
				else if (string("open exit") == input_line) {
					if (string("exit") == cur_room->name) {
						end_game = 1;
						cout << "Game Over" << endl;
					}
					else {
						cout << "Not at Exit." << endl;
					}
				}
				else if (string("take") == cur_command) {
					user_in_split = split(input_line, ' ');
					if (user_in_split.size() != 2) {
						cout << "Error" << endl;
					}
					else {
						item_op = getItem(user_in_split.at(1));
						if (item_op == NULL) {
							cout << "Item: not found" << endl;
						}
						else {
							if (searchInventory(user_in_split.at(1))) {
								cout << "You already have that." << endl;
							}
							else if (cur_room->name != item_op->owner) {
								container_check = getContainer(item_op->owner);
								if (container_check){
									for (vector<Container *>::iterator itr_container = cur_room->containers.begin(); itr_container != cur_room->containers.end(); ++itr_container) {
										if ((*itr_container)->name == item_op->owner && container_check->open == 1) {
											cout << "Item " << user_in_split.at(1) << " added to inventory." << endl;
											inventory.push_back(item_op);
											taken = 1;
										}
									}
									if (!taken) {
										cout << "Can't take that." << endl;
									}
									else {
										taken = 0;
									}
								}
								else {
									cout << "Can't take that." << endl;
								}
							}
							else {
								cout << "Item " << user_in_split.at(1) << " added to inventory." << endl;
								inventory.push_back(item_op);
							}
						}
					}
				}
				else if (string("read") == cur_command) {
					user_in_split = split(input_line, ' ');
					if (user_in_split.size() != 2) {
						cout << "Error" << endl;
					}
					else {
						item_op = searchInventory(user_in_split.at(1));
						if (item_op == NULL) {
							cout << "Item: " << user_in_split.at(1) << " not in inventory" << endl;
						}
						else if  (item_op->writing != ""){
							cout << item_op->writing << endl;
						}
						else {
							cout << "Nothing written." << endl;
						}
					}
				}
			}
		}
		else{
			cout << "Error" << endl;
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
		cout << (*itr_inv)->name << ", ";
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

Creature * Game::getCreature(string cr_name){
	vector<Creature *>::iterator itr_creature = creatures.begin();
	while (itr_creature != creatures.end()){
		if ((*itr_creature)->name == cr_name) {
			return (*itr_creature);
		}
		++itr_creature;
	}
	return NULL;
}

Container * Game::getContainer(string co_name){
	vector<Container *>::iterator itr_container = containers.begin();
	while (itr_container != containers.end()){
		if ((*itr_container)->name == co_name) {
			return (*itr_container);
		}
		++itr_container;

	}
	return NULL;
}

Item * Game::getItem(string i_name){
	vector<Item *>::iterator itr_item = items.begin();
	while (itr_item != items.end()){
		if ((*itr_item)->name == i_name) {
			return (*itr_item);
		}
		++itr_item;
	}
	return NULL;
}

Room * Game::switchRoom(string cur_command, Room * cur_room){
	vector<Border *>::iterator itr_border = cur_room->borders.begin();
	while (itr_border != cur_room->borders.end() && (*itr_border)->direction != cur_command) {
		if (cur_command == string(1, (*itr_border)->direction.at(0))) {
			Room * next_room = getRoom((*itr_border)->name);
			cout << next_room->description << endl;
			return next_room;
		}
		else {
			cout << "Can't go that way." << endl;
			return NULL;
		}
		++itr_border;
	}
	return NULL;
}

Item * Game::searchInventory(string i_name) {
	vector<Item *>::iterator itr_item = inventory.begin();
	while (itr_item != inventory.end()) {
		if ((*itr_item)->name == i_name) {
			return (*itr_item);
		}
	}
	return NULL;
}

Trigger * Game::getReadyTriggers(Room * cur_room, string cur_command){
	Trigger * ret_trigger = NULL;

	ret_trigger = cur_room->searchTriggers(cur_command);
	if (ret_trigger){
		if (determineStatus(ret_trigger)){
			return ret_trigger;
		}
		else {
			return NULL;
		}
	}
	return NULL;
}

unsigned char Game::determineStatus(Trigger * trig){

	string loc_owner = "";
	string loc_object = "";

	Item * object = NULL;

	if (string("single") == trig->type && trig->ready == 1){
		return 0;
	}

	vector<Condition *>::iterator itr_conditions = trig->conditions.begin();
	for (itr_conditions; itr_conditions != trig->conditions.end(); ++itr_conditions){
		if ((*itr_conditions)->has == string("yes")){
			loc_owner = (*itr_conditions)->owner;
			if (loc_owner == string("")) {

			}
			else if (loc_owner == string("inventory")) {
				loc_object = (*itr_conditions)->object;
				object = searchInventory(loc_object);
				if (NULL != object) {
					trig->ready = 1;
					return 1;
				}
				else {
					return 0;
				}
			}
		}
		else if ((*itr_conditions)->has == string("no")){
			loc_owner = (*itr_conditions)->owner;
			if (loc_owner == string("")){

			}
			else if (loc_owner == string("inventory")){
				loc_object = (*itr_conditions)->object;
				object = searchInventory(loc_object);
				if (NULL == object){
					trig->ready = 1;
					return 1;
				}
				else {
					return 0;
				}
			}
		}
		else{
			cout << "Error" << endl;
		}
	}
	return 0;
}

void Game::runTrigger(Trigger * trig) {
	if (trig->ready) {
		cout << trig->print << endl;
	}
}

vector<string> Game::split(string in, char delim) {
	vector<string> ret_split;
	unsigned int b_cur = 0;
	unsigned int e_cur = 0;
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == delim) {
			e_cur = i;
			ret_split.push_back(in.substr(b_cur, e_cur));
			if (b_cur + 1 < in.length()) {
				b_cur = i + 1;
			}
			else {
				return ret_split;
			}
		}
	}
	ret_split.push_back(in.substr(b_cur, e_cur + 1));
	return ret_split;
}

unsigned char Game::validateCommand(string cur_command){
	string valid_commands[] = {"n", "s", "e", "w", "i",
							   "take", "open", "open exit",
	                           "read", "drop", "put", "turn on",
							   "attack"};
	for (int i = 0; i < NUM_COMMANDS; i++){
		if (cur_command == valid_commands[i]){
			return 1;
		}
	}
	return 0;
}

void Game::initItems() {
	Item * item_check = NULL;
	for (vector<Room *>::iterator itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
		for (vector<Item *>::iterator itr_item = (*itr_room)->items.begin(); itr_item != (*itr_room)->items.end(); ++itr_item) {
			item_check = getItem((*itr_item)->name);
			if (item_check) {
				item_check->owner = (*itr_room)->name;
			}
		}
	}
	for (vector<Container *>::iterator itr_container = containers.begin(); itr_container != containers.end(); ++itr_container) {
		for (vector<Item *>::iterator itr_item = (*itr_container)->items.begin(); itr_item != (*itr_container)->items.end(); ++itr_item) {
			item_check = getItem((*itr_item)->name);
			if (item_check) {
				item_check->owner = (*itr_container)->name;
			}
		}
	}
}