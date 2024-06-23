#include <Game.h>

using namespace std;

int main()
{
	Game* game = new Game();

	while (game->running())
	{
		game->update();
		game->render();
	}

	delete game;
	game = nullptr;

	return 0;
}
