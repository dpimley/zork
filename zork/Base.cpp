#include "Base.h"

Base::Base() {}

Base::~Base() {}

Trigger * Base::searchTriggers(string cur_command) {
	vector<Trigger *>::iterator itr_trigger = triggers.begin();
	while (itr_trigger != itr_trigger) {
		if ((*itr_trigger)->command == cur_command) {
			return (*itr_trigger);
		}
	}
	return NULL;
}
