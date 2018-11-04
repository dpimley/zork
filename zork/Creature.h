#ifndef CREATURE_H
#define CREATURE_H

#include "Base.h"

class Creature : public Base {
public:
	Creature(xml_node<> * acc);
	virtual ~Creature();

	string name = "";
	string status = "";
	string description = "";
	vector<string> vulnerabilities;
	Trigger * attack;
};


#endif /* CONTAINER_H */