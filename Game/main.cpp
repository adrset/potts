#include "Game.h"

int main(int argc, char** argv) {
	Game* game = new Game(800, 600, "Blank");
	game->start();
	return 0;
}
