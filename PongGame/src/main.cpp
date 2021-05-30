#include "Game.h"

//C/C++ libraries
#include <iostream>

int main()
{
	Game *game = Game::GetInstance();

	if (game->Init())
		return -1;


	//Main Loop
	while(!game->ShouldClose())
	{
		game->Clear();

		//Draw Shit
		game->Draw();
		game->Update();

		game->SwapBuffers();
		game->PollEvents();
	}


	return 0;
}