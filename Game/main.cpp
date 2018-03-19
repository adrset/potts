#include "Game.h"

int main(int argc, char** argv) {
	Game* game = new Game(400, 400, "Potts");
	game->start();
	return 0;
}
