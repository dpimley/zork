#include "Item.h"

Item::Item(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (NAME == acc->name()){
			name = acc->value();
		}
		else if (STATUS == acc->name()){
			status = acc->value();
		}
		else if (DESCRIPTION == acc->name()){
			description = acc->value();
		}
		else if (WRITING == acc->name()){
			writing = acc->value();
		}
		else if (TURN_ON == acc->name()){
			xml_node<> * _tmp1 = acc->first_node("print");
			xml_node<> * _tmp2 = acc->first_node("action");

			turn_on.print = _tmp1->value();
			turn_on.action = _tmp2->value();
		}
		else if (TRIGGER == acc->name()){
			Trigger * _tmp1 = new Trigger(acc);

			triggers.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Item::~Item() {}