#ifndef BASE_H
#define BASE_H

#include <iostream>

#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"
#include "rapidxml-1.13\rapidxml_print.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;

class Base {
public:
	Base();
	virtual ~Base();
};

#endif /* BASE_H */