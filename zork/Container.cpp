#include "Container.h"

Container::Container(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (NAME == acc->name){
			name = acc->value;
		} 
		else if (STATUS == acc->name){
			status = acc->value;
		} 
		else if (DESCRIPTION == acc->name){
			description = acc->value;
		} 
		else if (VULNERABILITY == acc->name){
			accept.push_back(acc->value);
		}
		else if (ITEM == acc->name){
			Item * _tmp1 = new Item(acc);
			items.push_back(_tmp1);
		}
		else if (TRIGGER == acc->name){
			Trigger * _tmp1 = new Trigger(acc);
			triggers.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Container::~Container() {}