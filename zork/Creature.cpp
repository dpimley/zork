#include "Creature.h"

Creature::Creature(xml_node<> * acc){
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
			vulnerabilities.push_back(acc->value);
		}
		else if (ATTACK == acc->name){
			attack = new Trigger(acc);
		}
		else if (TRIGGER == acc->name){
			Trigger * _tmp1 = new Trigger(acc);
			triggers.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Creature::~Creature() {}