#include "Trigger.h"

Trigger::Trigger(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (COMMAND == acc->name){
			this->command = acc->value;
		}
		else if (TYPE == acc->name){
			this->type = acc->value;
		}
		else if (PRINT == acc->name){
			this->print = acc->value;
		}
		else if (ACTION == acc->name){
			this->action = acc->value;
		}
		else if (CONDITION == acc->name){
			_condition * _tmp1 = new _condition;
			if (acc->first_node(HAS)){
				_tmp1->object = acc->first_node(HAS)->value;
			}
			else if (acc->first_node(OBJECT)){
				_tmp1->object = acc->first_node(OBJECT)->value;
			}
			else if (acc->first_node(OWNER)){
				_tmp1->object = acc->first_node(OWNER)->value;
			}
			else if (acc->first_node(STATUS)){
				_tmp1->object = acc->first_node(STATUS)->value;
			}
			conditions.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Trigger::~Trigger() {}