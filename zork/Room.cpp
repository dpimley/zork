#include "Room.h"

Room::Room(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (NAME == acc->name()){
			name = acc->value();
		}
		else if (STATUS == acc->name()){
			status = acc->value();
		}
		else if (TYPE == acc->name()){
			type = acc->value();
		}
		else if (DESCRIPTION == acc->name()){
			description = acc->value();
		}
		else if (BORDER == acc->name()){
			Border * _tmp_b = new Border(acc);
			borders.push_back(_tmp_b);
		}
		else if (CONTAINER == acc->name()){
			Container * _tmp_c = new Container(acc);
			_tmp_c->name = acc->value();
			containers.push_back(_tmp_c);
		}
		else if (ITEM == acc->name()){
			Item * _tmp_i = new Item(acc);
			_tmp_i->name = acc->value();
			items.push_back(_tmp_i);
		}
		else if (CREATURE == acc->name()){
			Creature * _tmp_cr = new Creature(acc);
			_tmp_cr->name = acc->value();
			creatures.push_back(_tmp_cr);
		}
		else if (TRIGGER == acc->name()){
			Trigger * _tmp_t = new Trigger(acc);
			triggers.push_back(_tmp_t);
		}
		acc = acc->next_sibling();
	}
}

Room::~Room() {}