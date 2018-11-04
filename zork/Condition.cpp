#include "Condition.h"

Condition::Condition(xml_node<> * acc) {
	acc = acc->first_node();
	while (acc != NULL) {
		if (acc->first_node("has")) {
			has = acc->first_node("has")->value();
		}
		else if (acc->first_node("object")) {
			object = acc->first_node("object")->value();
		}
		else if (acc->first_node("owner")) {
			owner = acc->first_node("owner")->value();
		}
		else if (acc->first_node("status")) {
			status = acc->first_node("status")->value();
		}
		acc = acc->next_sibling();
	}
}

Condition::~Condition() {}