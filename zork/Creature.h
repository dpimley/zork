#ifndef CREATURE_H
#define CREATURE_H

#include "Base.h"

class Creature : public Base {
public:
	Creature(xml_node<> * acc);
	virtual ~Creature();

	vector<string> vulnerabilities;
	Trigger * attack = NULL;;
};


#endif /* CONTAINER_H */