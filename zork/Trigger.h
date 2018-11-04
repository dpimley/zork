#ifndef TRIGGER_H
#define TRIGGER_H

#include "Condition.h"

using namespace rapidxml;
using namespace std;

class Trigger {
public:
	Trigger(xml_node<> * acc);
	virtual ~Trigger();

	vector<Condition *> conditions;
	string command = "";
	string type = "single";
	string print = "";
	string action = "";
	unsigned int times_executed = 0;
	unsigned int ready = 0;
};

#endif /* TRIGGER_H */