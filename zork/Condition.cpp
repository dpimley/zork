#include "Condition.h"

Condition::Condition(xml_node<> * acc) {
	acc = acc->first_node();
	while (acc != NULL) {
		if (string("has") == acc->name()) {
			has = acc->value();
		}
		else if (string("object") == acc->name()) {
			object = acc->value();
		}
		else if (string("owner") == acc->name()) {
			owner = acc->value();
		}
		else if (string("status") == acc->name()) {
			status = acc->value();
		}
		acc = acc->next_sibling();
	}
}

Condition::~Condition() {}