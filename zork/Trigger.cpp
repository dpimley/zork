#include "Trigger.h"

Trigger::Trigger(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (COMMAND == acc->name()){
			command = acc->value();
		}
		else if (TYPE == acc->name()){
			type = acc->value();
		}
		else if (PRINT == acc->name()){
			print = acc->value();
		}
		else if (ACTION == acc->name()){
			action = acc->value();
		}
		else if (CONDITION == acc->name()){
			Condition * _tmp1 = new Condition(acc);
			conditions.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Trigger::~Trigger() {}