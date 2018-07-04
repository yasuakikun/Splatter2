#include "Game.h"

int main()
{
	Game& game = Game::Instance();

	game.Initalize();
	game.Run();
	game.Terminent();
}
