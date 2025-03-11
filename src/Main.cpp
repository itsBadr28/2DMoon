#include <iostream>
#include "Game/Game.h"

int main(int argr, char* argv[]) {
	Game game;

	game.Initialize();
	game.Run();
	game.Destroy();

    return 0;
}