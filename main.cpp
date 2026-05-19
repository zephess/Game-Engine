#include "Game.h"
#undef main
int main() {
	Game game;
	if (!game.init()) {
		return -1;
	}
	game.run();
	game.shutdown();
	return 0;
}