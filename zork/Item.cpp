#include "Item.h"

Item::Item(xml_node<> * acc){
	acc = acc->first_node;
	while (acc != NULL){
		if ("name" == acc->name){
			this->name = acc->value;
		}
		else if ("status" == acc->name){
			this->status = acc->value;
		}
		else if ("description" == acc->name){
			this->description = acc->value;
		}
		else if ("writing" == acc->name){
			this->description = acc->value;
		}
		else if ("turnon" == acc->name){
			xml_node<> * _tmp1 = acc->first_node("print");
			xml_node<> * _tmp2 = acc->first_node("action");

			this->turn_on.print = _tmp1->value;
			this->turn_on.action = _tmp2->value;
		}
	}
}

Item::~Item() {}