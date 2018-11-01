#include "Border.h"

Border::Border(xml_node<> * acc) {
	acc = acc->first_node();

	while (acc != NULL) {
		if (NAME == acc->name()) {
			name = acc->value();
		}
		else if (DIRECTION == acc->name()) {
			direction = acc->value();
		}
		acc = acc->next_sibling();
	}
}

Border::~Border() {}