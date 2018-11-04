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
	string input_line = "";
	string cur_command = "";
	vector<string> user_in_split;
	Item * item_op = NULL;
	Item * item_inv = NULL;
	Trigger * trigger_check = NULL;
	Container * container_check = NULL;
	Container * container_gl = NULL;
	unsigned char trig_priority = 0;
	unsigned char taken = 0;
	unsigned char drop_token = 0;

	Room * cur_room = getRoom("Entrance");
	if (NULL == cur_room){
		cout << "Game Over" << endl;
		end_game = 1;
		return;
	}
	cout << cur_room->description << endl;

	while (!end_game){
		getline(cin, input_line);
		cur_command = input_line.substr(0, input_line.find(" "));
		user_in_split = split(input_line, ' ');

		if (validateCommand(cur_command)){
			trigger_check = getReadyTriggers(cur_room, cur_command);
			if (trigger_check){
				cout << trigger_check->print << endl;
				actionExecute(trigger_check->action);
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
				else if (string("open") == cur_command) {
					user_in_split = split(input_line, ' ');
					if (user_in_split.size() != 2) {
						cout << "Error" << endl;
					}
					else {
						container_check = getContainer(user_in_split.at(1));
						if (container_check == NULL) {
							cout << "Container: not found" << endl;
						}
						else {
							for (vector<Container *>::iterator itr_container = cur_room->containers.begin(); itr_container != cur_room->containers.end(); ++itr_container) {
								if ((*itr_container)->name == user_in_split.at(1)) {
									if (container_check->accept.size() == 0) {
										container_check->open = 1;
										printContainerItems(container_check);
									}
									else {

									}
								}
							}
						}
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
				else if (string("drop") == cur_command) {
					user_in_split = split(input_line, ' ');
					if (user_in_split.size() != 2) {
						cout << "Error" << endl;
					}
					else {
						item_op = getItem(user_in_split.at(1));
						if (!item_op) {
							cout << "Item not found." << endl;
						}
						else {
							item_inv = searchInventory(user_in_split.at(1));
							if (!item_inv) {
								cout << "You don't have that." << endl;
							}
							else {
								vector<Item *>::iterator itr_item = inventory.begin();
								int i = 0;
								for (itr_item; itr_item != inventory.end(); ++itr_item) {
									if ((*itr_item)->name == user_in_split.at(1)) {
										drop_token = 1;
									}
									if (!drop_token) {
										i++;
									}
								}
								if (drop_token) {
									item_op->owner = cur_room->name;
									inventory.erase(inventory.begin() + i);
									cout << user_in_split.at(1) << " dropped." << endl;
								}
							}
						}
					}
				}
				else if (string("turn") == user_in_split.at(0) && string("on") == user_in_split.at(1) && user_in_split.size() == 3) {
					item_inv = searchInventory(user_in_split.at(2));
					if (!item_inv) {
						cout << "You don't have that." << endl;
					}
					else {
						item_op = getItem(user_in_split.at(2));
						if (item_op->turn_on_action == string("") || item_op->turn_on_print == string("")) {
							cout << "You can't turn that on." << endl;
						}
						else {
							cout << item_op->turn_on_print << endl;
							actionExecute(item_op->turn_on_action);
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

				runNCTriggers(cur_room);
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
	unsigned char first_item = 1;
	cout << "Inventory: ";
	vector<Item *>::iterator itr_inv = inventory.begin();
	for (itr_inv; itr_inv != inventory.end(); ++itr_inv){
		if (first_item) {
			cout << (*itr_inv)->name;
			first_item = 0;
		}
		else {
			cout << ", " << (*itr_inv)->name;
		}
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
	if (inventory.size() == 0) {
		return NULL;
	}
	vector<Item *>::iterator itr_item = inventory.begin();
	while (itr_item != inventory.end()) {
		if ((*itr_item)->name == i_name) {
			return (*itr_item);
		}
		++itr_item;
	}
	return NULL;
}

void Game::printContainerItems(Container * cont) {
	if (cont->items.size() == 0) {
		cout << cont->name << " is empty" << endl;
		return;
	}
	vector<Item *>::iterator item_container = cont->items.begin();
	unsigned char first_c_item = 1;
	for (item_container; item_container != cont->items.end(); ++item_container) {
		if (first_c_item) {
			cout << cont->name << " contains " << (*item_container)->name;
			first_c_item = 0;
		}
		else {
			cout << ", " << (*item_container)->name;
		}
	}
	cout << endl;
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

void Game::runNCTriggers(Room * cur_room) {
	Creature * s_creature = NULL;
	Container * s_container = NULL;
	Item * s_item = NULL;
	Trigger * ret_trigger = NULL;

	vector<Creature *>::iterator itr_creature = cur_room->creatures.begin(); 
	vector<Container *>::iterator itr_container = cur_room->containers.begin();
	vector<Item *>::iterator itr_item = cur_room->items.begin();

	for (itr_creature; itr_creature != cur_room->creatures.end(); ++itr_creature) {
		s_creature = getCreature((*itr_creature)->name);
		if (s_creature) {
			ret_trigger = s_creature->searchNCTriggers();
			if (ret_trigger && determineStatus(ret_trigger)) {
				cout << ret_trigger->print << endl;
				actionExecute(ret_trigger->action);
			}
		}
	}

	for (itr_container; itr_container != cur_room->containers.end(); ++itr_container) {
		s_container = getContainer((*itr_container)->name);
		if (s_container) {
			ret_trigger = s_container->searchNCTriggers();
			if (ret_trigger && determineStatus(ret_trigger)) {
				cout << ret_trigger->print << endl;
				actionExecute(ret_trigger->action);
			}
		}
	}

	for (itr_item; itr_item != cur_room->items.end(); ++itr_item) {
		s_item = getItem((*itr_item)->name);
		if (s_item) {
			ret_trigger = s_item->searchNCTriggers();
			if (ret_trigger && determineStatus(ret_trigger)) {
				cout << ret_trigger->print << endl;
				actionExecute(ret_trigger->action);
			}
		}
	}
}

unsigned char Game::determineStatus(Trigger * trig){

	string loc_owner = "";
	string loc_object = "";

	Item * object = NULL;

	vector<Condition *>::iterator itr_conditions;

	if (string("single") == trig->type && trig->ready == 1){
		return 0;
	}

	if (trig->conditions.size() == 0) {
		trig->ready = 1;
		return 1;
	}
	itr_conditions = trig->conditions.begin();
	for (itr_conditions; itr_conditions != trig->conditions.end(); ++itr_conditions) {
		if ((*itr_conditions)->status != string("")) {
			Base * object = searchAll((*itr_conditions)->object);
			if (!object) {
				cout << "No Object with that name." << endl;
			}
			else if ((*itr_conditions)->status == object->status) {
				trig->ready = 1;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	itr_conditions = trig->conditions.begin();
	for (itr_conditions; itr_conditions != trig->conditions.end(); ++itr_conditions){
		if ((*itr_conditions)->has == string("yes")){
			loc_owner = (*itr_conditions)->owner;
			if (loc_owner == string("")) {
				cout << "Error No Owner" << endl;
				return 0;
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
				cout << "Error No Owner" << endl;
				return 0;
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

vector<string> Game::split(string in, char delim) {
	vector<string> ret_split;
	unsigned int b_cur = 0;
	unsigned int e_cur = 0;
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == delim) {
			e_cur = i;
			ret_split.push_back(in.substr(b_cur, e_cur - b_cur));
			if (i + 1 < in.length()) {
				b_cur = i + 1;
			}
			else {
				return ret_split;
			}
		}
	}
	e_cur = in.length();
	ret_split.push_back(in.substr(b_cur, e_cur - b_cur));
	return ret_split;
}

unsigned char Game::validateCommand(string cur_command){
	string valid_commands[] = {"n", "s", "e", "w", "i",
							   "take", "open", "open exit",
	                           "read", "drop", "put", "turn",
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
void Game::actionExecute(string action) {
	vector<string> user_input_split = split(action, ' ');

	Base * object = NULL;

	if (string("Add") == user_input_split.at(0) && user_input_split.size() == 4) {

	}
	else if (string("Delete") == user_input_split.at(0) && user_input_split.size() == 2) {
		actionDelete(user_input_split.at(1));
	}
	else if (string("Update") == user_input_split.at(0) && user_input_split.size() == 4) {
		object = searchAll(user_input_split.at(1));
		if (object) {
			object->status = user_input_split.at(3);
		}
		else {
			cout << "No object found." << endl;
		}
	}
	else if (string("Game") == user_input_split.at(0) && string("Over") == user_input_split.at(1) && user_input_split.size() == 2) {
		cout << "Game Over" << endl;
		end_game = 1;
	}
}

Base * Game::searchAll(string o_name) {
	for (vector<Room *>::iterator itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
		if ((*itr_room)->name == o_name) {
			return (*itr_room);
		}
	}
	for (vector<Creature *>::iterator itr_creature = creatures.begin(); itr_creature != creatures.end(); ++itr_creature) {
		if ((*itr_creature)->name == o_name) {
			return (*itr_creature);
		}
	}
	for (vector<Container *>::iterator itr_container = containers.begin(); itr_container != containers.end(); ++itr_container) {
		if ((*itr_container)->name == o_name) {
			return (*itr_container);
		}
	}
	for (vector<Item *>::iterator itr_item = items.begin(); itr_item != items.end(); ++itr_item) {
		if ((*itr_item)->name == o_name) {
			return (*itr_item);
		}
	}
}

void Game::actionDelete(string o_name) {
	Room * s_room = getRoom(o_name);
	Creature * s_creature = getCreature(o_name);
	Container * s_container = getContainer(o_name);
	Item * s_item = getItem(o_name);

	vector<Room *>::iterator itr_room;
	vector<Creature *>::iterator itr_creature;
	vector<Container *>::iterator itr_container;
	vector<Item *>::iterator itr_item;
	vector<Border *>::iterator itr_border;

	unsigned char i = 0;
	unsigned char drop_token = 0;

	if (s_room) {
		for (itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
			for (itr_border = (*itr_room)->borders.begin(); itr_border != (*itr_room)->borders.end(); ++itr_border) {
				if ((*itr_border)->name == o_name) {
					(*itr_border)->name = "";
					return;
				}
			}
		}
	}
	else if (s_creature) {
		for (itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
			for (itr_creature = (*itr_room)->creatures.begin(); itr_creature != (*itr_room)->creatures.end(); ++itr_creature) {
				if ((*itr_creature)->name == o_name) {
					drop_token = 1;
					(*itr_room)->creatures.erase((*itr_room)->creatures.begin() + i);
					return;
				}
				if (!drop_token) {
					i++;
				}
			}
			i = 0;
		}
	}
	else if (s_container) {
		for (itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
			for (itr_container = (*itr_room)->containers.begin(); itr_container != (*itr_room)->containers.end(); ++itr_container) {
				if ((*itr_container)->name == o_name) {
					drop_token = 1;
					(*itr_room)->containers.erase((*itr_room)->containers.begin() + i);
					return;
				}
				if (!drop_token) {
					i++;
				}
			}
			i = 0;
		}
	}
	else if (s_item) {
		for (itr_container = containers.begin(); itr_container != containers.end(); ++itr_container) {
			for (itr_item = (*itr_container)->items.begin(); itr_item != (*itr_container)->items.end(); ++itr_item) {
				if ((*itr_item)->name == o_name) {
					drop_token = 1;
					(*itr_container)->items.erase((*itr_container)->items.begin() + i);
					return;
				}
				if (!drop_token) {
					i++;
				}
			}
			i = 0;
		}
		for (itr_room = rooms.begin(); itr_room != rooms.end(); ++itr_room) {
			for (itr_item = (*itr_room)->items.begin(); itr_item != (*itr_room)->items.end(); ++itr_item) {
				if ((*itr_item)->name == o_name) {
					drop_token = 1;
					(*itr_room)->items.erase((*itr_room)->items.begin() + i);
					return;
				}
				if (!drop_token) {
					i++;
				}
			}
			i = 0;
		}
	}
}