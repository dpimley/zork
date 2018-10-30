#include "Base.h"

int main(int argc, char * * argv){
	xml_document<> doc;
	xml_node<> * root_node;
	std::ifstream theFile("sample.txt.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("map");
	return EXIT_SUCCESS;
}