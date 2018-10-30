#ifndef CREATURE_H
#define CREATURE_H

#include "Base.h"

class Creature {
public:
	Creature(xml_node<> * acc);
	virtual ~Creature();

	string name = "";
	string status = "";
	string description = "";
	vector<string> vulnerabilities;

};


#endif /* CONTAINER_H */