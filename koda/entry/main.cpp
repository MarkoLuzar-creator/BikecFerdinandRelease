#define SDL_MAIN_HANDLED
#define SDL_WIN32_VIDEO_WINDOW
#include <SDL.h>
#include <ctime>
#include <cstdlib>
#include "Game.h"
#include "Data.h"

int WinMain(int argc, char *argv[])
{
	srand(time(0));

	Data::GetInstance().Read();
	Game bikecFerdinand;
	bikecFerdinand.Init();
	while (bikecFerdinand.isRunning)
	{
		bikecFerdinand.Update();
	}
	bikecFerdinand.Cleanup();
	Data::GetInstance().Write();
}