#include "Base.h"
#include "Game.h"

int main(int argc, char * * argv){
	Game * game = new Game(argv[1]);
	//game->printObjects();
	game->start();
	return EXIT_SUCCESS;
}