#ifndef CREATURE_H
#define CREATURE_H

#include "Base.h"
#include "Trigger.h"

class Creature {
public:
	Creature(xml_node<> * acc);
	virtual ~Creature();

	string name = "";
	string status = "";
	string description = "";
	vector<string> vulnerabilities;
	Trigger * attack;
	vector<Trigger *> triggers;
};


#endif /* CONTAINER_H */