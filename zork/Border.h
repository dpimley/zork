#ifndef BORDER_H
#define BORDER_H

#include "Base.h"

class Border {
public:
	Border(xml_node<> * acc);
	virtual ~Border();

	string name = "";
	string direction = "";
};

#endif /* BORDER_H */
