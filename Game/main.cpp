#include "Game.h"

int main(int argc, char** argv) {
	Game* game = new Game(400, 400, "Blank");
	game->start();
	return 0;
}
