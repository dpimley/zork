#ifndef TRIGGER_H
#define TRIGGER_H

#include "Base.h"

typedef struct _condition{
	string has;
	string object;
	string owner;
	string status;
}_condition;

class Trigger {
public:
	Trigger(xml_node<> * acc);
	virtual ~Trigger();

	vector<_condition *> conditions;
	string command = "";
	string type = "";
	string print = "";
	string action = "";
};

#endif /* TRIGGER_H */