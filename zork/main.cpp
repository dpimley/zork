#include "Base.h"
#include "Game.h"

int main(int argc, char * * argv){
	Game * game = new Game("sample.txt.xml");
	game->printObjects();
	return EXIT_SUCCESS;
}