#include "Trigger.h"

Trigger::Trigger(xml_node<> * acc){
	acc = acc->first_node();
	while (acc != NULL){
		if (COMMAND == acc->name()){
			this->command = acc->value();
		}
		else if (TYPE == acc->name()){
			this->type = acc->value();
		}
		else if (PRINT == acc->name()){
			this->print = acc->value();
		}
		else if (ACTION == acc->name()){
			this->action = acc->value();
		}
		else if (CONDITION == acc->name()){
			_condition * _tmp1 = new _condition;
			if (acc->first_node("has")){
				_tmp1->object = acc->first_node("has")->value();
			}
			else if (acc->first_node("object")){
				_tmp1->object = acc->first_node("object")->value();
			}
			else if (acc->first_node("owner")){
				_tmp1->object = acc->first_node("owner")->value();
			}
			else if (acc->first_node("status")){
				_tmp1->object = acc->first_node("status")->value();
			}
			conditions.push_back(_tmp1);
		}
		acc = acc->next_sibling();
	}
}

Trigger::~Trigger() {}