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
	string type = "";
	string print = "";
	string action = "";
};

#endif /* TRIGGER_H */